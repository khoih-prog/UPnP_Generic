/****************************************************************************************************************************
  UPnP_Generic_Impl.h
  
  For all Generic boards such as ESP8266, ESP32, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1,Teensy
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00, ENC28J60, Native Ethernet shields
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under GPL-3.0 license
  Version: 3.2.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  3.1.4  K Hoang      23/09/2020 Initial coding for Generic boards using many WiFi/Ethernet modules/shields.
  3.1.5  K Hoang      28/09/2020 Fix issue with nRF52 and STM32F/L/H/G/WB/MP1 using ESP8266/ESP32-AT
  3.2.0  K Hoang      11/06/2021 Add support to RP2040-based boards using ESP-AT, WiFiNINA, W5x00 / ENC28J60
 *****************************************************************************************************************************/

#ifndef UPnP_Generic_Impl_h
#define UPnP_Generic_Impl_h

#include <Arduino.h>

IPAddress ipMulti(239, 255, 255, 250);            // multicast address for SSDP
IPAddress connectivityTestIp(64, 233, 187, 99);   // Google
IPAddress ipNull(0, 0, 0, 0);                     // indication to update rules when the IP of the device changes

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];        // buffer to hold incoming packet UDP_TX_PACKET_MAX_SIZE=8192
char responseBuffer[UDP_TX_RESPONSE_MAX_SIZE];

char body_tmp[1200];
char integer_string[32];

SOAPAction SOAPActionGetSpecificPortMappingEntry  = {.name = "GetSpecificPortMappingEntry"};
SOAPAction SOAPActionDeletePortMapping            = {.name = "DeletePortMapping"};

/////////////////////////////////////////////////////////////////////

String IPAddresstoString(IPAddress ipAddress)
{
  char szRet[16];
  sprintf(szRet, "%u.%u.%u.%u", ipAddress[0], ipAddress[1], ipAddress[2], ipAddress[3]);

  return String(szRet);
}

/////////////////////////////////////////////////////////////////////

// timeoutMs - timeout in milli seconds for the operations of this class, 0 for blocking operation
UPnP::UPnP(unsigned long timeoutMs = 20000)
{
  _timeoutMs        = timeoutMs;
  _lastUpdateTime   = 0;
  _consequtiveFails = 0;
  _headRuleNode     = NULL;

  clearGatewayInfo(&_gwInfo);

  UPNP_LOGINFO1(F("UDP_TX_PACKET_MAX_SIZE="), UDP_TX_PACKET_MAX_SIZE);
  UPNP_LOGINFO1(F("UDP_TX_RESPONSE_MAX_SIZE="), UDP_TX_RESPONSE_MAX_SIZE);
}

/////////////////////////////////////////////////////////////////////

UPnP::~UPnP()
{
}

/////////////////////////////////////////////////////////////////////

void UPnP::addPortMappingConfig(IPAddress ruleIP, int rulePort, String ruleProtocol, int ruleLeaseDuration, String ruleFriendlyName)
{
  static int index      = 0;
  upnpRule *newUpnpRule = new upnpRule();
  newUpnpRule->index    = index++;

#if UPNP_USING_ETHERNET
  newUpnpRule->internalAddr = (ruleIP == Ethernet.localIP()) ? ipNull : ruleIP;  // for automatic IP change handling
#else
  newUpnpRule->internalAddr = (ruleIP == WiFi.localIP()) ? ipNull : ruleIP;  // for automatic IP change handling
#endif

  UPNP_LOGINFO1(F("newUpnpRule="), newUpnpRule->internalAddr);

  newUpnpRule->internalPort     = rulePort;
  newUpnpRule->externalPort     = rulePort;
  newUpnpRule->leaseDuration    = ruleLeaseDuration;
  newUpnpRule->protocol         = ruleProtocol;
  newUpnpRule->devFriendlyName  = ruleFriendlyName;

  // linked list insert
  upnpRuleNode *newUpnpRuleNode = new upnpRuleNode();
  newUpnpRuleNode->upnpRule     = newUpnpRule;
  newUpnpRuleNode->next         = NULL;

  if (_headRuleNode == NULL)
  {
    _headRuleNode = newUpnpRuleNode;
  }
  else
  {
    upnpRuleNode *currNode = _headRuleNode;

    while (currNode->next != NULL)
    {
      currNode = currNode->next;
    }

    currNode->next = newUpnpRuleNode;
  }
}

/////////////////////////////////////////////////////////////////////

portMappingResult UPnP::commitPortMappings()
{
  if (!_headRuleNode)
  {
    UPNP_LOGINFO(F("ERROR: No UPnP port mapping set."));

    return EMPTY_PORT_MAPPING_CONFIG;
  }

  unsigned long startTime = millis();

#if UPNP_USING_ETHERNET
  // verify WiFi is connected
  if (!testConnectivity(startTime))
  {
    UPNP_LOGINFO(F("ERROR: not connected to Ethernet Network, can't continue"));

    return NETWORK_ERROR;
  }
#else
  // verify WiFi is connected
  if (!testConnectivity(startTime))
  {
    UPNP_LOGINFO(F("ERROR: not connected to WiFi, can't continue"));

    return NETWORK_ERROR;
  }
#endif

  // get all the needed IGD information using SSDP if we don't have it already
  if (!isGatewayInfoValid(&_gwInfo))
  {
    getGatewayInfo(&_gwInfo, startTime);

    if (_timeoutMs > 0 && (millis() - startTime > _timeoutMs))
    {
      UPNP_LOGINFO(F("ERROR: Invalid router info, stop"));

      _UPnPClient.stop();
      return NETWORK_ERROR;
    }

    delay(1000);  // longer delay to allow more time for the router to update its rules
  }

  UPNP_LOGINFO3(F("Port :"), _gwInfo.port, F(", actionPort :"), _gwInfo.actionPort );

  // double verify gateway information is valid
  if (!isGatewayInfoValid(&_gwInfo))
  {
    UPNP_LOGINFO(F("ERROR: Invalid router info, stop"));

    _UPnPClient.stop();
    return NETWORK_ERROR;
  }

  if (_gwInfo.port != _gwInfo.actionPort) 
  {
    // in this case we need to connect to a different port
    UPNP_LOGINFO(F("Connection port changed, disconnecting from IGD"));

    _UPnPClient.stop();
  }

  bool allPortMappingsAlreadyExist  = true;   // for debug
  int addedPortMappings             = 0;      // for debug
  upnpRuleNode *currNode            = _headRuleNode;

  while (currNode != NULL)
  {
    UPNP_LOGINFO1(F("Verify port mapping for rule :"), currNode->upnpRule->devFriendlyName);

    bool currPortMappingAlreadyExists = true;  // for debug

    // TODO: since verifyPortMapping connects to the IGD then addPortMappingEntry can skip it
    while (!verifyPortMapping(&_gwInfo, currNode->upnpRule))
    {
      // need to add the port mapping
      currPortMappingAlreadyExists  = false;
      allPortMappingsAlreadyExist   = false;

      if (_timeoutMs > 0 && (millis() - startTime > _timeoutMs))
      {
        UPNP_LOGINFO(F("Timeout adding a port mapping"));

        _UPnPClient.stop();
        return TIMEOUT;
      }
      
      addPortMappingEntry(&_gwInfo, currNode->upnpRule);
      delay(1000);  // longer delay to allow more time for the router to update its rules
    }

    if (!currPortMappingAlreadyExists)
    {
      addedPortMappings++;

      UPNP_LOGINFO1(F("Added Port mapping :"), currNode->upnpRule->devFriendlyName);
    }

    currNode = currNode->next;
  }

  _UPnPClient.stop();

  if (allPortMappingsAlreadyExist)
  {
    UPNP_LOGINFO(F("All port mappings found in IGD, doing nothing"));

    return ALREADY_MAPPED;
  }
  else
  {
    // addedPortMappings is at least 1 here
    if (addedPortMappings > 1)
    {
      UPNP_LOGINFO1(addedPortMappings, F("UPnP port mappings added"));
    }
    else
    {
      UPNP_LOGINFO(F("One UPnP port mapping added"));
    }
  }

  return PORT_MAP_SUCCESS;
}

/////////////////////////////////////////////////////////////////////

bool UPnP::getGatewayInfo(gatewayInfo *deviceInfo, long startTime)
{
  while (!connectUDP())
  {
    UPNP_FLUSH();
    
    if (_timeoutMs > 0 && (millis() - startTime > _timeoutMs))
    {
      UPNP_LOGINFO(F("\nTimeout connect UDP"));
      UPNP_FLUSH();

      //_udpClient.stop();
      return false;
    }

    delay(500);

    UPNP_LOGINFO0(".");
  }

  UPNP_LOGINFO0("\n");

#if UPNP_USING_ETHERNET
  IPAddress gatewayIP = Ethernet.gatewayIP();
#else
  IPAddress gatewayIP = WiFi.gatewayIP();
#endif

  UPNP_LOGINFO1(F("GW IP ="), gatewayIP);
  
  broadcastMSearch();
  
  while (!waitForUnicastResponseToMSearch(deviceInfo, gatewayIP))
  {
    if (_timeoutMs > 0 && (millis() - startTime > _timeoutMs))
    {
      UPNP_LOGINFO(F("Timeout GW router to respond to M-SEARCH message"));

      _udpClient.stop();
      return false;
    }

    delay(1);
  }

  // close the UDP connection
  _udpClient.stop();

  // connect to IGD (TCP connection)
  while (!connectToIGD(deviceInfo->host, deviceInfo->port))
  {
    if (_timeoutMs > 0 && (millis() - startTime > _timeoutMs))
    {
      UPNP_LOGINFO(F("Timeout connect to IGD"));

      _UPnPClient.stop();
      return false;
    }

    delay(500);
  }

  // get event urls from the gateway IGD
  while (!getIGDEventURLs(deviceInfo))
  {
    if (_timeoutMs > 0 && (millis() - startTime > _timeoutMs))
    {
      UPNP_LOGINFO(F("Timeout adding a new port mapping"));

      _UPnPClient.stop();
      return false;
    }

    delay(500);
  }

  return true;
}

/////////////////////////////////////////////////////////////////////

void UPnP::clearGatewayInfo(gatewayInfo *deviceInfo)
{
  deviceInfo->host = IPAddress(0, 0, 0, 0);
  deviceInfo->port = 0;
  deviceInfo->path = "";
  deviceInfo->actionPort = 0;
  deviceInfo->actionPath = "";
  deviceInfo->serviceTypeName = "";
}

/////////////////////////////////////////////////////////////////////

bool UPnP::isGatewayInfoValid(gatewayInfo *deviceInfo)
{
  UPNP_LOGINFO3(F("isGatewayInfoValid :"), deviceInfo->host, F(", port :"), deviceInfo->port);
  UPNP_LOGINFO3(F("Path :"), deviceInfo->path, F(", actionPort :"), deviceInfo->actionPort);
  UPNP_LOGINFO3(F("actionPath :"), deviceInfo->actionPath, F(", serviceTypeName :"), deviceInfo->serviceTypeName);

  if (deviceInfo->host == IPAddress(0, 0, 0, 0)
      || deviceInfo->port == 0
      || deviceInfo->path.length() == 0
      || deviceInfo->actionPort == 0)
  {
    UPNP_LOGINFO(F("Gateway info not valid"));

    return false;
  }

  UPNP_LOGINFO(F("Gateway info valid"));

  return true;
}

/////////////////////////////////////////////////////////////////////

portMappingResult UPnP::updatePortMappings(unsigned long intervalMs, callback_function fallback)
{
  if (millis() - _lastUpdateTime >= intervalMs)
  {
    UPNP_LOGINFO(F("Updating port mapping"));

    // fallback
    if (_consequtiveFails >= MAX_NUM_OF_UPDATES_WITH_NO_EFFECT)
    {
      UPNP_LOGDEBUG1(F("ERROR: Many failures on updatePortMappings. Failed times :"), _consequtiveFails);

      _consequtiveFails = 0;
      clearGatewayInfo(&_gwInfo);

      if (fallback != NULL)
      {
        UPNP_LOGDEBUG(F("Executing fallback method"));

        fallback();
      }

      return TIMEOUT;
    }

    // }
    // else if (_consequtiveFails > 300)
    // {
    //   ESP.restart();  // should test as last resort
    //  return;
    // }

    portMappingResult result = commitPortMappings();

    if (result == PORT_MAP_SUCCESS || result == ALREADY_MAPPED)
    {
      _lastUpdateTime = millis();
      _UPnPClient.stop();
      _consequtiveFails = 0;
      return result;
    }
    else
    {
      _lastUpdateTime += intervalMs / 2;  // delay next try

      UPNP_LOGINFO(F("ERROR: While updating UPnP port mapping"));

      _UPnPClient.stop();
      _consequtiveFails++;
      return result;
    }
  }

  _UPnPClient.stop();

  return NOP;  // no need to check yet
}

/////////////////////////////////////////////////////////////////////

bool UPnP::testConnectivity(unsigned long startTime)
{

#if UPNP_USING_ETHERNET

#else

  UPNP_LOGINFO1(F("Testing WiFi connection for IP :"), WiFi.localIP());

  while (WiFi.status() != WL_CONNECTED)
  {
    if (_timeoutMs > 0 && startTime > 0 && (millis() - startTime > _timeoutMs))
    {
      UPNP_LOGINFO(F(" ==> Timeout verify WiFi connection"));

      _UPnPClient.stop();
      return false;
    }

    delay(200);

    UPNP_LOGINFO0(".");
  }

  UPNP_LOGINFO0(" ==> GOOD\n");

#endif

  _UPnPClient.connect(connectivityTestIp, 80);

  while (!_UPnPClient.connected())
  {
    if (startTime + TCP_CONNECTION_TIMEOUT_MS > millis())
    {
      UPNP_LOGINFO(F("Internet connection BAD"));

      _UPnPClient.stop();
      return false;
    }
  }

  UPNP_LOGINFO(F("Internet connection GOOD"));

  _UPnPClient.stop();
  
  return true;
}

/////////////////////////////////////////////////////////////////////

bool UPnP::verifyPortMapping(gatewayInfo *deviceInfo, upnpRule *rule_ptr)
{
  if (!applyActionOnSpecificPortMapping(&SOAPActionGetSpecificPortMappingEntry , deviceInfo, rule_ptr))
  {
    return false;
  }

  // TODO: extract the current lease duration and return it instead of a boolreadStringUntil
  bool isPORT_MAP_SUCCESS = false;
  bool detectedChangedIP = false;

  while (_UPnPClient.available())
  {
    String line = _UPnPClient.readStringUntil('\r');

    UPNP_LOGDEBUG0(line);

    if (line.indexOf(F("errorCode")) >= 0)
    {
      isPORT_MAP_SUCCESS = false;

      // flush response and exit loop
      while (_UPnPClient.available())
      {
        line = _UPnPClient.readStringUntil('\r');

        UPNP_LOGDEBUG0(line);
      }

      continue;
    }

    if (line.indexOf(F("NewInternalClient")) >= 0)
    {
      String content = getTagContent(line, F("NewInternalClient"));

      if (content.length() > 0)
      {

#if UPNP_USING_ETHERNET
        IPAddress ipAddressToVerify = (rule_ptr->internalAddr == ipNull) ? Ethernet.localIP() : rule_ptr->internalAddr;
#else
        IPAddress ipAddressToVerify = (rule_ptr->internalAddr == ipNull) ? WiFi.localIP() : rule_ptr->internalAddr;
#endif


        // KH, to verify
#if (ESP32 || ESP8266)
        if (content == ipAddressToVerify.toString())
#else
        if (content == IPAddresstoString(ipAddressToVerify))
#endif
        {
          isPORT_MAP_SUCCESS = true;
        }
        else
        {
          detectedChangedIP = true;
        }
      }
    }
  }

  UPNP_LOGDEBUG0("\n");

  _UPnPClient.stop();

  if (isPORT_MAP_SUCCESS)
  {
    UPNP_LOGINFO(F("Port mapping found in IGD"));
  }
  else if (detectedChangedIP)
  {
    UPNP_LOGINFO(F("Detected change in IP"));

    removeAllPortMappingsFromIGD();
  }
  else
  {
    UPNP_LOGINFO(F("Couldn't find port mapping in IGD"));
  }

  return isPORT_MAP_SUCCESS;
}

/////////////////////////////////////////////////////////////////////

bool UPnP::deletePortMapping(gatewayInfo *deviceInfo, upnpRule *rule_ptr)
{
  if (!applyActionOnSpecificPortMapping(&SOAPActionDeletePortMapping , deviceInfo, rule_ptr))
  {
    return false;
  }

  bool isPORT_MAP_SUCCESS = false;

  while (_UPnPClient.available())
  {
    String line = _UPnPClient.readStringUntil('\r');

    UPNP_LOGDEBUG0(line);

    if (line.indexOf(F("errorCode")) >= 0)
    {
      isPORT_MAP_SUCCESS = false;

      // flush response and exit loop
      while (_UPnPClient.available())
      {
        line = _UPnPClient.readStringUntil('\r');

        UPNP_LOGDEBUG0(line);
      }
      continue;
    }

    if (line.indexOf(F("DeletePortMappingResponse")) >= 0)
    {
      isPORT_MAP_SUCCESS = true;
    }
  }

  return isPORT_MAP_SUCCESS;
}

/////////////////////////////////////////////////////////////////////

bool UPnP::applyActionOnSpecificPortMapping(SOAPAction *soapAction, gatewayInfo *deviceInfo, upnpRule *rule_ptr)
{
  UPNP_LOGINFO3(F("Apply action :"), soapAction->name, F(" on port mapping :"), rule_ptr->devFriendlyName);

  // connect to IGD (TCP connection) again, if needed, in case we got disconnected after the previous query
  unsigned long timeout = millis() + TCP_CONNECTION_TIMEOUT_MS;

  if (!_UPnPClient.connected())
  {
    while (!connectToIGD(deviceInfo->host, deviceInfo->actionPort))
    {
      if (millis() > timeout)
      {
        UPNP_LOGDEBUG(F("Timeout connect to IGD"));

        _UPnPClient.stop();
        return false;
      }

      delay(500);
    }
  }

// KH, Somehow nRF52 and STM32 WiFi (ESP8266/ESP32-AT and WiFiNINA) don't behave well with FlashString
// Disable for nRF52 and STM32 WiFi now.
#if ( (ESP8266 || ESP32) || (UPNP_USING_ETHERNET && !UPNP_USING_NATIVE_ETHERNET) )

  strcpy_P(body_tmp, PSTR("<?xml version=\"1.0\"?>\r\n<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\r\n<s:Body>\r\n<u:"));
  strcat_P(body_tmp, soapAction->name);
  strcat_P(body_tmp, PSTR(" xmlns:u=\""));
  strcat_P(body_tmp, deviceInfo->serviceTypeName.c_str());
  strcat_P(body_tmp, PSTR("\">\r\n<NewRemoteHost></NewRemoteHost>\r\n<NewExternalPort>"));
  sprintf(integer_string, "%d", rule_ptr->internalPort);
  strcat_P(body_tmp, integer_string);
  strcat_P(body_tmp, PSTR("</NewExternalPort>\r\n<NewProtocol>"));
  strcat_P(body_tmp, rule_ptr->protocol.c_str());
  strcat_P(body_tmp, PSTR("</NewProtocol>\r\n</u:"));
  strcat_P(body_tmp, soapAction->name);
  strcat_P(body_tmp, PSTR(">\r\n</s:Body>\r\n</s:Envelope>\r\n"));

  sprintf(integer_string, "%d", strlen(body_tmp));

  _UPnPClient.print(F("POST "));

  _UPnPClient.print(deviceInfo->actionPath);
  _UPnPClient.println(F(" HTTP/1.1"));
  _UPnPClient.println(F("Connection: close"));
  _UPnPClient.println(F("Content-Type: text/xml; charset=\"utf-8\""));

  // KH, to verify
#if (ESP32 || ESP8266)
  _UPnPClient.println("Host: " + deviceInfo->host.toString() + ":" + String(deviceInfo->actionPort));
  UPNP_LOGINFO("Host: " + deviceInfo->host.toString() + ":" + String(deviceInfo->actionPort));
#else
  _UPnPClient.println("Host: " + String(deviceInfo->host) + ":" + String(deviceInfo->actionPort));
  UPNP_LOGINFO("Host: " + IPAddresstoString(deviceInfo->host) + ":" + String(deviceInfo->actionPort));
#endif

  _UPnPClient.print(F("SOAPAction: \""));
  _UPnPClient.print(deviceInfo->serviceTypeName);
  _UPnPClient.print(F("#"));
  _UPnPClient.print(soapAction->name);
  _UPnPClient.println(F("\""));
  _UPnPClient.print(F("Content-Length: "));
  _UPnPClient.println(integer_string);
  _UPnPClient.println();

  _UPnPClient.println(body_tmp);
  _UPnPClient.println();

#else

  strcpy(body_tmp, "<?xml version=\"1.0\"?>\r\n<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\r\n<s:Body>\r\n<u:");
  strcat(body_tmp, soapAction->name);
  strcat(body_tmp, " xmlns:u=\"");
  strcat(body_tmp, deviceInfo->serviceTypeName.c_str());
  strcat(body_tmp, "\">\r\n<NewRemoteHost></NewRemoteHost>\r\n<NewExternalPort>");
  sprintf(integer_string, "%d", rule_ptr->internalPort);
  strcat(body_tmp, integer_string);
  strcat(body_tmp, "</NewExternalPort>\r\n<NewProtocol>");
  strcat(body_tmp, rule_ptr->protocol.c_str());
  strcat(body_tmp, "</NewProtocol>\r\n</u:");
  strcat(body_tmp, soapAction->name);
  strcat(body_tmp, ">\r\n</s:Body>\r\n</s:Envelope>\r\n");

  sprintf(integer_string, "%d", strlen(body_tmp));

  _UPnPClient.print("POST ");

  _UPnPClient.print(deviceInfo->actionPath);
  _UPnPClient.println(" HTTP/1.1");
  _UPnPClient.println("Connection: close");
  _UPnPClient.println("Content-Type: text/xml; charset=\"utf-8\"");

  // KH, to verify
#if (ESP32 || ESP8266)
  _UPnPClient.println("Host: " + deviceInfo->host.toString() + ":" + String(deviceInfo->actionPort));
  UPNP_LOGINFO("Host: " + deviceInfo->host.toString() + ":" + String(deviceInfo->actionPort));
#else
  _UPnPClient.println("Host: " + String(deviceInfo->host) + ":" + String(deviceInfo->actionPort));
  UPNP_LOGINFO("Host: " + IPAddresstoString(deviceInfo->host) + ":" + String(deviceInfo->actionPort));
#endif

  _UPnPClient.print("SOAPAction: \"");
  _UPnPClient.print(deviceInfo->serviceTypeName);
  _UPnPClient.print("#");
  _UPnPClient.print(soapAction->name);
  _UPnPClient.println("\"");
  _UPnPClient.print("Content-Length: ");
  _UPnPClient.println(integer_string);
  _UPnPClient.println();

  _UPnPClient.println(body_tmp);
  _UPnPClient.println();
  
#endif

  UPNP_LOGDEBUG(body_tmp);

  timeout = millis() + TCP_CONNECTION_TIMEOUT_MS;

  while (_UPnPClient.available() == 0)
  {
    if (millis() > timeout)
    {
      UPNP_LOGDEBUG(F("TCP timeout retrieve port mappings"));

      _UPnPClient.stop();
      // TODO: in this case we might not want to add the ports right away
      // might want to try again or only start adding the ports after we definitely
      // did not see them in the router list
      return false;
    }
  }

  return true;
}

/////////////////////////////////////////////////////////////////////

void UPnP::removeAllPortMappingsFromIGD()
{
  upnpRuleNode *currNode = _headRuleNode;

  while (currNode != NULL)
  {
    deletePortMapping(&_gwInfo, currNode->upnpRule);
    currNode = currNode->next;
  }
}

// a single try to connect UDP multicast address and port of UPnP (239.255.255.250 and 1900 respectively)
// this will enable receiving SSDP packets after the M-SEARCH multicast message will be broadcasted
bool UPnP::connectUDP()
{

#if UPNP_USING_ETHERNET
  #if USE_BUILTIN_ETHERNET
    #warning Using LAN8742A Ethernet and STM32Ethernet Lib in UPnP
    // For STM32 built-in LAN8742A Ethernet using STM32Ethernet Lib
    // initialize, start listening on specified port. IPAddress here must be local, not ipMulti address
    // virtual uint8_t beginMulticast(IPAddress, uint16_t);
    if (_udpClient.beginMulticast(Ethernet.localIP(), UPNP_SSDP_PORT))
    {
      return true;
    }
  #else
    // initialize, start listening on specified port.
    // virtual uint8_t beginMulticast(IPAddress, uint16_t);
    if (_udpClient.beginMulticast(ipMulti, UPNP_SSDP_PORT))
    {
      return true;
    }
  #endif

#else

  #if defined(ESP8266)
    if (_udpClient.beginMulticast(WiFi.localIP(), ipMulti, UPNP_SSDP_PORT))
    {
      return true;
    }
  #else
    if (_udpClient.beginMulticast(ipMulti, UPNP_SSDP_PORT))
    {
      return true;
    }
  #endif

#endif    //UPNP_USING_ETHERNET

  //UPNP_LOGINFO(F("UDP connection failed"));
  UPNP_LOGINFO0(F("F"));

  return false;
}

/////////////////////////////////////////////////////////////////////

// broadcast an M-SEARCH message to initiate messages from SSDP devices
// the router should respond to this message by a packet sent to this device's unicast addresss on the
// same UPnP port (1900)
void UPnP::broadcastMSearch()
{

  UPNP_LOGINFO3(F("Sending M-SEARCH to :"), ipMulti, F(", Port :"), UPNP_SSDP_PORT);

#if UPNP_USING_ETHERNET
  // Start building up a packet to send to the multicast address
  _udpClient.beginPacket(ipMulti, UPNP_SSDP_PORT);
#else
  #if defined(ESP8266)
    _udpClient.beginPacketMulticast(ipMulti, UPNP_SSDP_PORT, WiFi.localIP());
  #elif (ESP32)
    _udpClient.beginMulticastPacket();
  #else
    // For remaining WiFi, such as WiFiNINA, WiFiEspAT using Ethernet beginPacket() interface
    // Start building up a packet to send to the multicast address
    _udpClient.beginPacket(ipMulti, UPNP_SSDP_PORT);
  #endif
  
#endif    // UPNP_USING_ETHERNET

// KH, Somehow nRF52 and STM32 WiFi (ESP8266/ESP32-AT and WiFiNINA) don't behave well with FlashString
// Disable for nRF52 and STM32 WiFi now.
#if ( (ESP8266 || ESP32) || (UPNP_USING_ETHERNET && !UPNP_USING_NATIVE_ETHERNET) )
  strcpy_P(body_tmp, PSTR("M-SEARCH * HTTP/1.1\r\n"));
  strcat_P(body_tmp, PSTR("HOST: 239.255.255.250:1900\r\n"));
  strcat_P(body_tmp, PSTR("MAN: \"ssdp:discover\"\r\n"));
  strcat_P(body_tmp, PSTR("MX: 5\r\n"));
  strcat_P(body_tmp, PSTR("ST: urn:schemas-upnp-org:device:InternetGatewayDevice:1\r\n\r\n"));
  #warning Using FlashString in UPnP
#else
  strcpy(body_tmp, "M-SEARCH * HTTP/1.1\r\n");
  strcat(body_tmp, "HOST: 239.255.255.250:1900\r\n");
  strcat(body_tmp, "MAN: \"ssdp:discover\"\r\n");
  strcat(body_tmp, "MX: 5\r\n");
  strcat(body_tmp, "ST: urn:schemas-upnp-org:device:InternetGatewayDevice:1\r\n\r\n");
  #warning Not using FlashString in UPnP
#endif

// KH, To check
#if UPNP_USING_ETHERNET && !UPNP_USING_NATIVE_ETHERNET
  _udpClient.write(body_tmp, strlen(body_tmp));
#else
  #if defined(ESP8266)
    _udpClient.write(body_tmp);
  #else
    _udpClient.print(body_tmp);
  #endif
#endif

  _udpClient.endPacket();

  UPNP_LOGDEBUG1(F("M-SEARCH sent :\n"), body_tmp);
}

/////////////////////////////////////////////////////////////////////

// Assuming an M-SEARCH message was broadcasted, wait for the response from the IGD (Internet Gateway Device)
// Note: the response from the IGD is sent back as unicast to this device
// Note: only gateway defined IGD response will be considered, the rest will be ignored
bool UPnP::waitForUnicastResponseToMSearch(gatewayInfo *deviceInfo, IPAddress gatewayIP)
{
  int packetSize = _udpClient.parsePacket();

  // only continue is a packet is available
  if (packetSize <= 0)
  {
    return false;
  }

  IPAddress remoteIP = _udpClient.remoteIP();

  // only continue if the packet was received from the gateway router
  if (remoteIP != gatewayIP)
  {
    return false;
  }

  UPNP_LOGINFO3(F("Received packet, size ="), packetSize, F(", IP ="), remoteIP);
  UPNP_LOGINFO1(F("Port ="), _udpClient.remotePort());

  // sanity check
  if (packetSize > UDP_TX_RESPONSE_MAX_SIZE)
  {
    UPNP_LOGDEBUG(F("Received packet size > than response buffer, not proceed."));

    return false;
  }

  int idx = 0;

  while (idx < packetSize)
  {
    memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE);
    int len = _udpClient.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

    if (len <= 0)
    {
      break;
    }

    UPNP_LOGDEBUG3(F("UDP packet read bytes ="), len, F(" out of"), packetSize);

    memcpy(responseBuffer + idx, packetBuffer, len);
    idx += len;
  }

  responseBuffer[idx] = '\0';

  UPNP_LOGDEBUG1(F("Gateway packet content:\n"), responseBuffer);

  // only continue if the packet is a response to M-SEARCH and it originated from a gateway device
  if (strstr(responseBuffer, INTERNET_GATEWAY_DEVICE) == NULL)
  {
    UPNP_LOGINFO(F("IGD not found"));

    return false;
  }

  UPNP_LOGINFO(F("IGD found"));

  String location = "";
  char* location_indexStart = strstr(responseBuffer, "location:");

  if (location_indexStart == NULL)
  {
    location_indexStart = strstr(responseBuffer, "Location:");
  }

  if (location_indexStart == NULL)
  {
    location_indexStart = strstr(responseBuffer, "LOCATION:");
  }

  if (location_indexStart != NULL)
  {
    location_indexStart += 9;  // "location:".length()
    char* location_indexEnd = strstr(location_indexStart, "\r\n");

    if (location_indexEnd != NULL)
    {
      int urlLength = location_indexEnd - location_indexStart;
      int arrLength = urlLength + 1;  // + 1 for '\0'
      // converting the start index to be inside the packetBuffer rather than responseBuffer
      char locationCharArr[arrLength];

      memcpy(locationCharArr, location_indexStart, urlLength);
      locationCharArr[arrLength - 1] = '\0';
      location = String(locationCharArr);
      location.trim();
    }
    else
    {
      UPNP_LOGDEBUG(F("ERROR: Can't extract value from LOCATION param"));

      return false;
    }
  }
  else
  {
    UPNP_LOGDEBUG(F("ERROR: LOCATION param not found"));

    return false;
  }

  UPNP_LOGINFO1(F("IGD location found :"), location);


  IPAddress host  = getHost(location);
  int       port  = getPort(location);
  String    path  = getPath(location);

  deviceInfo->host = host;
  deviceInfo->port = port;
  deviceInfo->path = path;
  
  // the following is the default and may be overridden if URLBase tag is specified
  deviceInfo->actionPort = port;

  UPNP_LOGINFO(host);
  UPNP_LOGINFO(port);
  UPNP_LOGINFO(path);

  return true;
}

/////////////////////////////////////////////////////////////////////

// a single trial to connect to the IGD (with TCP)
bool UPnP::connectToIGD(IPAddress host, int port)
{
  UPNP_LOGINFO3(F("Connecting to IGD with host :"), host, F(", port :"), port);

  if (_UPnPClient.connect(host, port))
  {
    UPNP_LOGINFO(F("Connected to IGD"));

    return true;
  }

  UPNP_LOGINFO(F("Not Connected to IGD"));

  return false;
}

/////////////////////////////////////////////////////////////////////

// updates deviceInfo with the commands' information of the IGD
bool UPnP::getIGDEventURLs(gatewayInfo *deviceInfo)
{
  UPNP_LOGINFO("called getIGDEventURLs");
  UPNP_LOGINFO3(F("deviceInfo->actionPath :"), deviceInfo->actionPath, F(", deviceInfo->path :"), deviceInfo->path);

  // make an HTTP request

// KH, Somehow nRF52 and STM32 WiFi (ESP8266/ESP32-AT and WiFiNINA) don't behave well with FlashString
// Disable for nRF52 and STM32 WiFi now.
#if ( (ESP8266 || ESP32) || (UPNP_USING_ETHERNET && !UPNP_USING_NATIVE_ETHERNET) )

  _UPnPClient.print(F("GET "));
  _UPnPClient.print(deviceInfo->path);
  _UPnPClient.println(F(" HTTP/1.1"));
  _UPnPClient.println(F("Content-Type: text/xml; charset=\"utf-8\""));
  //_UPnPClient.println(F("Connection: close"));

  // KH, to verify
#if (ESP32 || ESP8266)
  _UPnPClient.println("Host: " + deviceInfo->host.toString() + ":" + String(deviceInfo->actionPort));
#else
  _UPnPClient.println("Host: " + IPAddresstoString(deviceInfo->host) + ":" + String(deviceInfo->actionPort));
#endif


  _UPnPClient.println(F("Content-Length: 0"));
  _UPnPClient.println();
  
#else

  _UPnPClient.print("GET ");
  _UPnPClient.print(deviceInfo->path);
  _UPnPClient.println(" HTTP/1.1");
  _UPnPClient.println("Content-Type: text/xml; charset=\"utf-8\"");
  //_UPnPClient.println("Connection: close");

  _UPnPClient.println("Host: " + IPAddresstoString(deviceInfo->host) + ":" + String(deviceInfo->actionPort));

  _UPnPClient.println("Content-Length: 0");
  _UPnPClient.println();
    
#endif  

  // wait for the response
  unsigned long timeout = millis();

  while (_UPnPClient.available() == 0)
  {
    if (millis() - timeout > TCP_CONNECTION_TIMEOUT_MS)
    {
      UPNP_LOGDEBUG(F("TCP timeout execute getIGDEventURLs"));

      _UPnPClient.stop();

      return false;
    }
  }

  // read all the lines of the reply from server
  bool upnpServiceFound = false;
  bool urlBaseFound = false;

  while (_UPnPClient.available())
  {
    String line = _UPnPClient.readStringUntil('\r');
    int index_in_line = 0;

    UPNP_LOGDEBUG0("\nPrint line\n");
    UPNP_LOGDEBUG0(line);
    //UPNP_LOGDEBUG0("\nPrinted line\n");

    if (!urlBaseFound && line.indexOf(F("<URLBase>")) >= 0)
    {
      // e.g. <URLBase>http://192.168.1.1:5432/</URLBase>
      // Note: assuming URL path will only be found in a specific action under the 'controlURL' xml tag
      String baseUrl = getTagContent(line, "URLBase");

      if (baseUrl.length() > 0)
      {
        baseUrl.trim();
        IPAddress host = getHost(baseUrl);  // this is ignored, assuming router host IP will not change
        int port = getPort(baseUrl);
        deviceInfo->actionPort = port;

        UPNP_LOGINFO1(F("URLBase tag found :"), baseUrl);
        UPNP_LOGINFO3(F("Translated to base host :"), host, F(" and base port :"), port );

        urlBaseFound = true;
      }
    }

    // to support multiple <serviceType> tags
    int service_type_index_start = 0;

    int service_type_1_index = line.indexOf(UPNP_SERVICE_TYPE_TAG_START + UPNP_SERVICE_TYPE_1);

    if (service_type_1_index >= 0)
    {
      service_type_index_start = service_type_1_index;
      service_type_1_index = line.indexOf(UPNP_SERVICE_TYPE_TAG_END, service_type_index_start);
    }

    int service_type_2_index = line.indexOf(UPNP_SERVICE_TYPE_TAG_START + UPNP_SERVICE_TYPE_2);

    if (service_type_2_index >= 0)
    {
      service_type_index_start = service_type_2_index;
      service_type_2_index = line.indexOf(UPNP_SERVICE_TYPE_TAG_END, service_type_index_start);
    }

    if (!upnpServiceFound && service_type_1_index >= 0)
    {
      index_in_line += service_type_1_index;
      upnpServiceFound = true;
      deviceInfo->serviceTypeName = getTagContent(line.substring(service_type_index_start), UPNP_SERVICE_TYPE_TAG_NAME);

      UPNP_LOGINFO(deviceInfo->serviceTypeName + " service found!");

      // will start looking for 'controlURL' now
    }
    else if (!upnpServiceFound && service_type_2_index >= 0)
    {
      index_in_line += service_type_2_index;
      upnpServiceFound = true;
      deviceInfo->serviceTypeName = getTagContent(line.substring(service_type_index_start), UPNP_SERVICE_TYPE_TAG_NAME);

      UPNP_LOGINFO(deviceInfo->serviceTypeName + " service found!");
      // will start looking for 'controlURL' now
    }

    if (upnpServiceFound && (index_in_line = line.indexOf("<controlURL>", index_in_line)) >= 0)
    {
      String controlURLContent = getTagContent(line.substring(index_in_line), "controlURL");

      if (controlURLContent.length() > 0)
      {
        deviceInfo->actionPath = controlURLContent;

        UPNP_LOGINFO1(F("controlURL tag found! Setting actionPath to :"), controlURLContent);

        // clear buffer
        UPNP_LOGDEBUG(F("Flushing rest of response"));

        while (_UPnPClient.available())
        {
          _UPnPClient.read();
        }

        // now we have (upnpServiceFound && controlURLFound)
        return true;
      }
    }
  }

  return false;
}

/////////////////////////////////////////////////////////////////////

// assuming a connection to the IGD has been formed
// will add the port mapping to the IGD
bool UPnP::addPortMappingEntry(gatewayInfo *deviceInfo, upnpRule *rule_ptr)
{
  UPNP_LOGINFO(F("Called addPortMappingEntry"));

  // connect to IGD (TCP connection) again, if needed, in case we got disconnected after the previous query
  unsigned long timeout = millis() + TCP_CONNECTION_TIMEOUT_MS;

  if (!_UPnPClient.connected())
  {
    while (!connectToIGD(_gwInfo.host, _gwInfo.actionPort))
    {
      if (millis() > timeout)
      {
        UPNP_LOGDEBUG(F("Timeout connect to IGD"));

        _UPnPClient.stop();
        return false;
      }

      delay(500);
    }
  }

  UPNP_LOGINFO3(F("deviceInfo->actionPath :"), deviceInfo->actionPath, F(", deviceInfo->serviceTypeName :"), deviceInfo->serviceTypeName);

// KH, Somehow nRF52 and STM32 WiFi (ESP8266/ESP32-AT and WiFiNINA) don't behave well with FlashString
// Disable for nRF52 and STM32 WiFi now.
#if ( (ESP8266 || ESP32) || (UPNP_USING_ETHERNET && !UPNP_USING_NATIVE_ETHERNET) )

  strcpy_P(body_tmp, PSTR("<?xml version=\"1.0\"?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:AddPortMapping xmlns:u=\""));
  strcat_P(body_tmp, deviceInfo->serviceTypeName.c_str());
  strcat_P(body_tmp, PSTR("\"><NewRemoteHost></NewRemoteHost><NewExternalPort>"));
  sprintf(integer_string, "%d", rule_ptr->internalPort);
  strcat_P(body_tmp, integer_string);
  strcat_P(body_tmp, PSTR("</NewExternalPort><NewProtocol>"));
  strcat_P(body_tmp, rule_ptr->protocol.c_str());
  strcat_P(body_tmp, PSTR("</NewProtocol><NewInternalPort>"));
  sprintf(integer_string, "%d", rule_ptr->internalPort);
  strcat_P(body_tmp, integer_string);
  strcat_P(body_tmp, PSTR("</NewInternalPort><NewInternalClient>"));

#if UPNP_USING_ETHERNET
  IPAddress ipAddress = (rule_ptr->internalAddr == ipNull) ? Ethernet.localIP() : rule_ptr->internalAddr;
#else
  IPAddress ipAddress = (rule_ptr->internalAddr == ipNull) ? WiFi.localIP() : rule_ptr->internalAddr;
#endif

#if (ESP32 || ESP8266)
  strcat_P(body_tmp, ipAddress.toString().c_str());
#else
  strcat_P(body_tmp, IPAddresstoString(ipAddress).c_str());
#endif

  strcat_P(body_tmp, PSTR("</NewInternalClient><NewEnabled>1</NewEnabled><NewPortMappingDescription>"));
  strcat_P(body_tmp, rule_ptr->devFriendlyName.c_str());
  strcat_P(body_tmp, PSTR("</NewPortMappingDescription><NewLeaseDuration>"));
  sprintf(integer_string, "%d", rule_ptr->leaseDuration);
  strcat_P(body_tmp, integer_string);
  strcat_P(body_tmp, PSTR("</NewLeaseDuration></u:AddPortMapping></s:Body></s:Envelope>"));

  sprintf(integer_string, "%d", strlen(body_tmp));

  _UPnPClient.print(F("POST "));
  _UPnPClient.print(deviceInfo->actionPath);
  _UPnPClient.println(F(" HTTP/1.1"));
  //_UPnPClient.println(F("Connection: close"));
  _UPnPClient.println(F("Content-Type: text/xml; charset=\"utf-8\""));

#if (ESP32 || ESP8266)
  _UPnPClient.println("Host: " + deviceInfo->host.toString() + ":" + String(deviceInfo->actionPort));
#else
  _UPnPClient.println("Host: " + IPAddresstoString(deviceInfo->host) + ":" + String(deviceInfo->actionPort));
#endif

  //_UPnPClient.println(F("Accept: */*"));
  //_UPnPClient.println(F("Content-Type: application/x-www-form-urlencoded"));
  _UPnPClient.print(F("SOAPAction: \""));
  _UPnPClient.print(deviceInfo->serviceTypeName);
  _UPnPClient.println(F("#AddPortMapping\""));

  _UPnPClient.print(F("Content-Length: "));
  _UPnPClient.println(integer_string);
  _UPnPClient.println();

  _UPnPClient.println(body_tmp);
  _UPnPClient.println();
  
#else

  strcpy(body_tmp, "<?xml version=\"1.0\"?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:AddPortMapping xmlns:u=\"");
  strcat(body_tmp, deviceInfo->serviceTypeName.c_str());
  strcat(body_tmp, "\"><NewRemoteHost></NewRemoteHost><NewExternalPort>");
  sprintf(integer_string, "%d", rule_ptr->internalPort);
  strcat(body_tmp, integer_string);
  strcat(body_tmp, "</NewExternalPort><NewProtocol>");
  strcat(body_tmp, rule_ptr->protocol.c_str());
  strcat(body_tmp, "</NewProtocol><NewInternalPort>");
  sprintf(integer_string, "%d", rule_ptr->internalPort);
  strcat(body_tmp, integer_string);
  strcat(body_tmp, "</NewInternalPort><NewInternalClient>");

#if UPNP_USING_ETHERNET
  IPAddress ipAddress = (rule_ptr->internalAddr == ipNull) ? Ethernet.localIP() : rule_ptr->internalAddr;
#else
  IPAddress ipAddress = (rule_ptr->internalAddr == ipNull) ? WiFi.localIP() : rule_ptr->internalAddr;
#endif

  strcat(body_tmp, IPAddresstoString(ipAddress).c_str());

  strcat(body_tmp, "</NewInternalClient><NewEnabled>1</NewEnabled><NewPortMappingDescription>");
  strcat(body_tmp, rule_ptr->devFriendlyName.c_str());
  strcat(body_tmp, "</NewPortMappingDescription><NewLeaseDuration>");
  sprintf(integer_string, "%d", rule_ptr->leaseDuration);
  strcat(body_tmp, integer_string);
  strcat(body_tmp, "</NewLeaseDuration></u:AddPortMapping></s:Body></s:Envelope>");

  sprintf(integer_string, "%d", strlen(body_tmp));

  _UPnPClient.print("POST ");
  _UPnPClient.print(deviceInfo->actionPath);
  _UPnPClient.println(" HTTP/1.1");
  //_UPnPClient.println("Connection: close");
  _UPnPClient.println("Content-Type: text/xml; charset=\"utf-8\"");

#if (ESP32 || ESP8266)
  _UPnPClient.println("Host: " + deviceInfo->host.toString() + ":" + String(deviceInfo->actionPort));
#else
  _UPnPClient.println("Host: " + IPAddresstoString(deviceInfo->host) + ":" + String(deviceInfo->actionPort));
#endif

  //_UPnPClient.println("Accept: */*");
  //_UPnPClient.println("Content-Type: application/x-www-form-urlencoded");
  _UPnPClient.print("SOAPAction: \"");
  _UPnPClient.print(deviceInfo->serviceTypeName);
  _UPnPClient.println("#AddPortMapping\"");

  _UPnPClient.print("Content-Length: ");
  _UPnPClient.println(integer_string);
  _UPnPClient.println();

  _UPnPClient.println(body_tmp);
  _UPnPClient.println();
  
#endif  

  UPNP_LOGDEBUG1(F("Content-Length :"), integer_string);
  UPNP_LOGDEBUG(body_tmp);

  timeout = millis();

  while (_UPnPClient.available() == 0)
  {
    if (millis() - timeout > TCP_CONNECTION_TIMEOUT_MS)
    {
      UPNP_LOGDEBUG(F("TCP timeout add a port mapping"));

      _UPnPClient.stop();

      return false;
    }
  }

  // TODO: verify PORT_MAP_SUCCESS
  bool isPORT_MAP_SUCCESS = true;

  while (_UPnPClient.available())
  {
    String line = _UPnPClient.readStringUntil('\r');

    if (line.indexOf(F("errorCode")) >= 0)
    {
      isPORT_MAP_SUCCESS = false;
    }

    UPNP_LOGDEBUG0(line);
  }

  UPNP_LOGDEBUG0("\n");

  if (!isPORT_MAP_SUCCESS)
  {
    _UPnPClient.stop();
  }

  return isPORT_MAP_SUCCESS;
}

/////////////////////////////////////////////////////////////////////

bool UPnP::printAllPortMappings()
{
  // verify gateway information is valid
  // TODO: use this _gwInfo to skip the UDP part completely if it is not empty
  if (!isGatewayInfoValid(&_gwInfo))
  {
    UPNP_LOGINFO(F("Invalid router info, can't continue"));

    return false;
  }

  upnpRuleNode *ruleNodeHead_ptr = NULL;
  upnpRuleNode *ruleNodeTail_ptr = NULL;

  unsigned long startTime = millis();
  bool reachedEnd = false;
  int index = 0;

  while (!reachedEnd)
  {
    // connect to IGD (TCP connection) again, if needed, in case we got disconnected after the previous query
    if (!_UPnPClient.connected())
    {
      while (!connectToIGD(_gwInfo.host, _gwInfo.actionPort))
      {
        if (_timeoutMs > 0 && (millis() - startTime > _timeoutMs))
        {
          UPNP_LOGINFO(F("Timeout connect to IGD"));

          _UPnPClient.stop();
          return false;
        }
        delay(1000);
      }
    }

    UPNP_LOGINFO1(F("Sending query for index :"), index);
    
// KH, Somehow nRF52 and STM32 WiFi (ESP8266/ESP32-AT and WiFiNINA) don't behave well with FlashString
// Disable for nRF52 and STM32 WiFi now.
#if ( (ESP8266 || ESP32) || (UPNP_USING_ETHERNET && !UPNP_USING_NATIVE_ETHERNET) )    

    strcpy_P(body_tmp, PSTR("<?xml version=\"1.0\"?>"
                            "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">"
                            "<s:Body>"
                            "<u:GetGenericPortMappingEntry xmlns:u=\""));
    strcat_P(body_tmp, _gwInfo.serviceTypeName.c_str());
    strcat_P(body_tmp, PSTR("\">"
                            "  <NewPortMappingIndex>"));

    sprintf(integer_string, "%d", index);
    strcat_P(body_tmp, integer_string);
    strcat_P(body_tmp, PSTR("</NewPortMappingIndex>"
                            "</u:GetGenericPortMappingEntry>"
                            "</s:Body>"
                            "</s:Envelope>"));

    sprintf(integer_string, "%d", strlen(body_tmp));

    _UPnPClient.print(F("POST "));
    _UPnPClient.print(_gwInfo.actionPath);
    _UPnPClient.println(F(" HTTP/1.1"));
    _UPnPClient.println(F("Connection: keep-alive"));
    _UPnPClient.println(F("Content-Type: text/xml; charset=\"utf-8\""));

    // KH, to verify
#if (ESP32 || ESP8266)
    _UPnPClient.println("Host: " + _gwInfo.host.toString() + ":" + String(_gwInfo.actionPort));
    UPNP_LOGINFO("Host: " + _gwInfo.host.toString() + ":" + String(_gwInfo.actionPort));
#else
    _UPnPClient.println("Host: " + String(_gwInfo.host) + ":" + String(_gwInfo.actionPort));
    UPNP_LOGINFO("Host: " + IPAddresstoString(_gwInfo.host) + ":" + String(_gwInfo.actionPort));
#endif

    _UPnPClient.print(F("SOAPAction: \""));
    _UPnPClient.print(_gwInfo.serviceTypeName);
    _UPnPClient.println(F("#GetGenericPortMappingEntry\""));

    _UPnPClient.print(F("Content-Length: "));
    _UPnPClient.println(integer_string);
    _UPnPClient.println();

    _UPnPClient.println(body_tmp);
    _UPnPClient.println();

#else

    strcpy(body_tmp, "<?xml version=\"1.0\"?>"
                            "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">"
                            "<s:Body>"
                            "<u:GetGenericPortMappingEntry xmlns:u=\"");
    strcat(body_tmp, _gwInfo.serviceTypeName.c_str());
    strcat(body_tmp, "\">"
                            "  <NewPortMappingIndex>");

    sprintf(integer_string, "%d", index);
    strcat(body_tmp, integer_string);
    strcat(body_tmp, "</NewPortMappingIndex>"
                            "</u:GetGenericPortMappingEntry>"
                            "</s:Body>"
                            "</s:Envelope>");

    sprintf(integer_string, "%d", strlen(body_tmp));

    _UPnPClient.print("POST ");
    _UPnPClient.print(_gwInfo.actionPath);
    _UPnPClient.println(" HTTP/1.1");
    _UPnPClient.println("Connection: keep-alive");
    _UPnPClient.println("Content-Type: text/xml; charset=\"utf-8\"");

    _UPnPClient.println("Host: " + String(_gwInfo.host) + ":" + String(_gwInfo.actionPort));
    UPNP_LOGINFO("Host: " + IPAddresstoString(_gwInfo.host) + ":" + String(_gwInfo.actionPort));

    _UPnPClient.print("SOAPAction: \"");
    _UPnPClient.print(_gwInfo.serviceTypeName);
    _UPnPClient.println("#GetGenericPortMappingEntry\"");

    _UPnPClient.print("Content-Length: ");
    _UPnPClient.println(integer_string);
    _UPnPClient.println();

    _UPnPClient.println(body_tmp);
    _UPnPClient.println();
    
#endif

    unsigned long timeout = millis();

    while (_UPnPClient.available() == 0)
    {
      if (millis() - timeout > TCP_CONNECTION_TIMEOUT_MS)
      {
        UPNP_LOGDEBUG(F("TCP timeout retrieve port mappings"));

        _UPnPClient.stop();
        return false;
      }
    }

    while (_UPnPClient.available())
    {
      String line = _UPnPClient.readStringUntil('\r');

      UPNP_LOGDEBUG0(line);

      if (line.indexOf(PORT_MAPPING_INVALID_INDEX) >= 0)
      {
        reachedEnd = true;
      }
      else if (line.indexOf(PORT_MAPPING_INVALID_ACTION) >= 0)
      {
        UPNP_LOGDEBUG(F("Invalid action while reading port mappings"));

        reachedEnd = true;
      }
      else if (line.indexOf(F("HTTP/1.1 500 ")) >= 0)
      {
        UPNP_LOGDEBUG(F("Internal server error, likely we got all the mappings"));

        reachedEnd = true;
      }
      else if (line.indexOf(F("GetGenericPortMappingEntryResponse")) >= 0)
      {
        upnpRule *rule_ptr = new upnpRule();
        rule_ptr->index = index;
        rule_ptr->devFriendlyName = getTagContent(line, "NewPortMappingDescription");
        String newInternalClient = getTagContent(line, "NewInternalClient");

        if (newInternalClient == "")
        {
          continue;
        }

        rule_ptr->internalAddr.fromString(newInternalClient);
        rule_ptr->internalPort = getTagContent(line, "NewInternalPort").toInt();
        rule_ptr->externalPort = getTagContent(line, "NewExternalPort").toInt();
        rule_ptr->protocol = getTagContent(line, "NewProtocol");
        rule_ptr->leaseDuration = getTagContent(line, "NewLeaseDuration").toInt();

        upnpRuleNode *currRuleNode_ptr = new upnpRuleNode();
        currRuleNode_ptr->upnpRule = rule_ptr;
        currRuleNode_ptr->next = NULL;

        if (ruleNodeHead_ptr == NULL)
        {
          ruleNodeHead_ptr = currRuleNode_ptr;
          ruleNodeTail_ptr = currRuleNode_ptr;
        }
        else
        {
          ruleNodeTail_ptr->next = currRuleNode_ptr;
          ruleNodeTail_ptr = currRuleNode_ptr;
        }
      }
    }

    index++;
    delay(250);
  }

  // print nicely and free heap memory
  UPNP_LOGWARN(F("IGD current port mappings:"));

  upnpRuleNode *curr_ptr = ruleNodeHead_ptr;
  upnpRuleNode *del_prt = ruleNodeHead_ptr;

  while (curr_ptr != NULL)
  {
    upnpRuleToString(curr_ptr->upnpRule);
    del_prt = curr_ptr;
    curr_ptr = curr_ptr->next;
    delete del_prt->upnpRule;
    delete del_prt;
  }

  _UPnPClient.stop();

  return true;
}

/////////////////////////////////////////////////////////////////////

void UPnP::printPortMappingConfig()
{
  UPNP_LOGINFO(F("UPnP configured port mappings:"));

  upnpRuleNode *currRuleNode = _headRuleNode;

  while (currRuleNode != NULL)
  {
    upnpRuleToString(currRuleNode->upnpRule);
    currRuleNode = currRuleNode->next;
  }
}

/////////////////////////////////////////////////////////////////////

// TODO: remove use of String
void UPnP::upnpRuleToString(upnpRule *rule_ptr)
{
  String index = String(rule_ptr->index);

  UPNP_LOGWARN0(index + ".");
  UPNP_LOGWARN0(getSpacesString(5 - (index.length() + 1)));

  String devFriendlyName = rule_ptr->devFriendlyName;

  UPNP_LOGWARN0(devFriendlyName + getSpacesString(30  - devFriendlyName.length()));

#if UPNP_USING_ETHERNET
  IPAddress ipAddress = (rule_ptr->internalAddr == ipNull) ? Ethernet.localIP() : rule_ptr->internalAddr;
#else
  IPAddress ipAddress = (rule_ptr->internalAddr == ipNull) ? WiFi.localIP() : rule_ptr->internalAddr;
#endif

  // KH, to verify
#if (ESP32 || ESP8266)
  String internalAddr = ipAddress.toString();
#else
  String internalAddr = IPAddresstoString(ipAddress);
#endif


  UPNP_LOGWARN0(internalAddr + getSpacesString(18 - internalAddr.length()));

  String internalPort = String(rule_ptr->internalPort);

  UPNP_LOGWARN0(internalPort + getSpacesString(7 - internalPort.length()));

  String externalPort = String(rule_ptr->externalPort);

  UPNP_LOGWARN0(externalPort + getSpacesString(7 - externalPort.length()));

  String protocol = rule_ptr->protocol;

  UPNP_LOGWARN0(protocol + getSpacesString(7 - protocol.length()));

  String leaseDuration = String(rule_ptr->leaseDuration);

  UPNP_LOGWARN0(leaseDuration + getSpacesString(7 - leaseDuration.length()) + "\n");
}

/////////////////////////////////////////////////////////////////////

String UPnP::getSpacesString(int num)
{
  if (num < 0)
  {
    num = 1;
  }

  String spaces = "";

  for (int i = 0; i < num; i++)
  {
    spaces += " ";
  }

  return spaces;
}

/////////////////////////////////////////////////////////////////////

/*
  char* UPnP::ipAddressToCharArr(IPAddress ipAddress)
  {
    char s[17];
    sprintf(s, "%d.%d.%d.%d", ipAddress[0], ipAddress[1], ipAddress[2], ipAddress[3]);
    s[16] = '\0';
    return s;
  }*/

/////////////////////////////////////////////////////////////////////

IPAddress UPnP::getHost(String url)
{
  IPAddress result(0, 0, 0, 0);

  if (url.indexOf(F("https://")) != -1)
  {
    url.replace("https://", "");
  }

  if (url.indexOf(F("http://")) != -1)
  {
    url.replace("http://", "");
  }

  int endIndex = url.indexOf('/');

  if (endIndex != -1)
  {
    url = url.substring(0, endIndex);
  }

  int colonsIndex = url.indexOf(':');

  if (colonsIndex != -1)
  {
    url = url.substring(0, colonsIndex);
  }

  result.fromString(url);

  return result;
}

/////////////////////////////////////////////////////////////////////

int UPnP::getPort(String url)
{
  int port = -1;

  if (url.indexOf(F("https://")) != -1)
  {
    url.replace("https://", "");
  }

  if (url.indexOf(F("http://")) != -1)
  {
    url.replace("http://", "");
  }

  int portEndIndex = url.indexOf("/");

  if (portEndIndex == -1)
  {
    portEndIndex = url.length();
  }

  url = url.substring(0, portEndIndex);
  int colonsIndex = url.indexOf(":");

  if (colonsIndex != -1)
  {
    url = url.substring(colonsIndex + 1, portEndIndex);
    port = url.toInt();
  }
  else
  {
    port = 80;
  }

  return port;
}

/////////////////////////////////////////////////////////////////////

String UPnP::getPath(String url)
{
  if (url.indexOf(F("https://")) != -1)
  {
    url.replace("https://", "");
  }

  if (url.indexOf(F("http://")) != -1)
  {
    url.replace("http://", "");
  }

  int firstSlashIndex = url.indexOf("/");

  if (firstSlashIndex == -1)
  {
    UPNP_LOGDEBUG("ERROR: Can't find path in url [" + url + "]");

    return "";
  }

  return url.substring(firstSlashIndex, url.length());
}

/////////////////////////////////////////////////////////////////////

String UPnP::getTagContent(const String &line, String tagName)
{
  int startIndex = line.indexOf("<" + tagName + ">");

  if (startIndex == -1)
  {
    UPNP_LOGDEBUG3(F("ERROR: Can't find tag content in line :"), line, F(" for start tag :"), tagName);

    return "";
  }

  startIndex += tagName.length() + 2;
  int endIndex = line.indexOf("</" + tagName + ">", startIndex);

  if (endIndex == -1)
  {
    UPNP_LOGDEBUG3(F("ERROR: Can't find tag content in line :"), line, F(" for end tag :"), tagName);

    return "";
  }

  return line.substring(startIndex, endIndex);
}

#endif    // UPnP_Generic_Impl_h
