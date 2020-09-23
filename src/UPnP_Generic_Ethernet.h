/****************************************************************************************************************************
  UPnP_Generic_Ethernet.h
  
  For all Generic boards such as ESP8266, ESP32, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266-AT, W5x00 Ethernet shields
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under MIT license
  Version: 3.1.4
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  3.1.4  K Hoang      23/09/2020 Initial coding for Generic boards using many WiFi/Ethernet modules/shields.
 *****************************************************************************************************************************/
 
#ifndef UPnP_Generic_Ethernet_h
#define UPnP_Generic_Ethernet_h

#include <Arduino.h>

#if ( USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE || USE_ETHERNET_ESP8266 || USE_ETHERNET_ENC )
  #ifdef USE_CUSTOM_ETHERNET
    #undef USE_CUSTOM_ETHERNET
  #endif
  #define USE_CUSTOM_ETHERNET   false
#endif

#if (USE_BUILTIN_ETHERNET)
  #include <LwIP.h>
  #include <STM32Ethernet.h>
  #warning Using LAN8742A Ethernet & STM32Ethernet lib
  #define SHIELD_TYPE           "LAN8742A Ethernet & STM32Ethernet Library"
#elif (USE_UIP_ETHERNET)
  #include "UIPEthernet.h"
  #warning Using ENC28J60 & UIPEthernet lib
  #define SHIELD_TYPE           "ENC28J60 & UIPEthernet Library"
#elif USE_ETHERNET3
  #include "Ethernet3.h"
  #warning Using W5x00 & Ethernet3 lib
  #define SHIELD_TYPE           "W5x00 & Ethernet3 Library"
#elif USE_ETHERNET2
  #include "Ethernet2.h"
  #warning Using W5x00 & Ethernet2 lib
  #define SHIELD_TYPE           "W5x00 & Ethernet2 Library"
#elif USE_ETHERNET_LARGE
  #include "EthernetLarge.h"
  #warning Using W5x00 & EthernetLarge lib
  #define SHIELD_TYPE           "W5x00 & EthernetLarge Library"
#elif USE_ETHERNET_ESP8266
  #include "Ethernet_ESP8266.h"
  #warning Using W5x00 & Ethernet_ESP8266 lib 
  #define SHIELD_TYPE           "W5x00 & Ethernet_ESP8266 Library" 
#elif USE_ETHERNET_ENC
  #include "EthernetENC.h"
  #warning Using ENC28J60 & EthernetENC lib
  #define SHIELD_TYPE           "ENC28J60 & EthernetENC Library"
#elif USE_CUSTOM_ETHERNET
  //#include "Ethernet_XYZ.h"
  #include "EthernetENC.h"
  #warning Using Custom Ethernet library. You must include a library and initialize.
  #define SHIELD_TYPE           "Custom Ethernet & Ethernet_XYZ Library"
#else
  #define USE_ETHERNET          true
  #include "Ethernet.h"
  #warning Using Ethernet lib
  #define SHIELD_TYPE           "W5x00 & Ethernet Library"
#endif

//#include <WiFiUdp.h>
//#include <WiFiClient.h>

#include <limits.h>

#define UPNP_DEBUG

// Simple Service Discovery Protocol (SSDP)
#define UPNP_SSDP_PORT                    1900
#define TCP_CONNECTION_TIMEOUT_MS         6000
#define INTERNET_GATEWAY_DEVICE           "urn:schemas-upnp-org:device:InternetGatewayDevice:1"
#define PORT_MAPPING_INVALID_INDEX        "<errorDescription>SpecifiedArrayIndexInvalid</errorDescription>"
#define PORT_MAPPING_INVALID_ACTION       "<errorDescription>Invalid Action</errorDescription>"

#define RULE_PROTOCOL_TCP                 "TCP"
#define RULE_PROTOCOL_UDP                 "UDP"

// after 6 tries of updatePortMappings we will execute the more extensive addPortMapping
#define MAX_NUM_OF_UPDATES_WITH_NO_EFFECT 6

// reduce max UDP packet size to conserve memory (by default UDP_TX_PACKET_MAX_SIZE=8192)

#ifdef UDP_TX_PACKET_MAX_SIZE
  #undef UDP_TX_PACKET_MAX_SIZE
#endif

#define UDP_TX_PACKET_MAX_SIZE            1000

#define UDP_TX_RESPONSE_MAX_SIZE          8192

const String UPNP_SERVICE_TYPE_1          = "urn:schemas-upnp-org:service:WANPPPConnection:";
const String UPNP_SERVICE_TYPE_2          = "urn:schemas-upnp-org:service:WANIPConnection:";
const String UPNP_SERVICE_TYPE_TAG_NAME   = "serviceType";
const String UPNP_SERVICE_TYPE_TAG_START  = "<serviceType>";
const String UPNP_SERVICE_TYPE_TAG_END    = "</serviceType>";

// TODO: idealy the SOAP actions should be verified as supported by the IGD before they are used
//      a struct can be created for each action and filled when the XML descriptor file is read
/*const String SOAPActions [] =
  {
    "AddPortMapping",
    "GetSpecificPortMappingEntry",
    "DeletePortMapping",
    "GetGenericPortMappingEntry",
    "GetExternalIPAddress"
  };*/

/*
  #define SOAP_ERROR_TAG "errorDescription";
  const String SOAPErrors [] =
  {
    "SpecifiedArrayIndexInvalid",
    "Invalid Action"
  };*/

/*
  enum soapActionResult
  {
  // TODO
  }*/

typedef struct _SOAPAction
{
  const char *name;
} SOAPAction;

typedef void (*callback_function)(void);

typedef struct _gatewayInfo
{
  // router info
  IPAddress host;
  int port;  // this port is used when getting router capabilities and xml files
  String path;  // this is the path that is used to retrieve router information from xml files

  // info for actions
  int actionPort;  // this port is used when performing SOAP API actions
  String actionPath;  // this is the path used to perform SOAP API actions
  String serviceTypeName;  // i.e "WANPPPConnection:1" or "WANIPConnection:1"
} gatewayInfo;

typedef struct _upnpRule
{
  int index;
  String devFriendlyName;
  IPAddress internalAddr;
  int internalPort;
  int externalPort;
  String protocol;
  int leaseDuration;
} upnpRule;

typedef struct _upnpRuleNode
{
  _upnpRule *upnpRule;
  _upnpRuleNode *next;
} upnpRuleNode;

enum portMappingResult
{
  PORT_MAP_SUCCESS,   // port mapping was added
  ALREADY_MAPPED,     // the port mapping is already found in the IGD
  EMPTY_PORT_MAPPING_CONFIG,
  NETWORK_ERROR,
  TIMEOUT,
  NOP  // the check is delayed
};

class UPnP
{
  public:
    UPnP(unsigned long timeoutMs);
    ~UPnP();
    
    // when the ruleIP is set to the current device IP, the IP of the rule will change if the device changes its IP
    // this makes sure the traffic will be directed to the device even if the IP chnages
    void                addPortMappingConfig(IPAddress ruleIP /* can be NULL */, int rulePort, String ruleProtocol, int ruleLeaseDuration, String ruleFriendlyName);
    portMappingResult   commitPortMappings();
    portMappingResult   updatePortMappings(unsigned long intervalMs, callback_function fallback = NULL /* optional */);
    bool                printAllPortMappings();
    void                printPortMappingConfig();  // prints all the port mappings that were added using `addPortMappingConfig`
    bool                testConnectivity(unsigned long startTime = 0);

  private:
    bool        connectUDP();
    void        broadcastMSearch();
    bool        waitForUnicastResponseToMSearch(gatewayInfo *deviceInfo, IPAddress gatewayIP);
    bool        getGatewayInfo(gatewayInfo *deviceInfo, long startTime);
    bool        isGatewayInfoValid(gatewayInfo *deviceInfo);
    void        clearGatewayInfo(gatewayInfo *deviceInfo);
    bool        connectToIGD(IPAddress host, int port);
    bool        getIGDEventURLs(gatewayInfo *deviceInfo);
    bool        addPortMappingEntry(gatewayInfo *deviceInfo, upnpRule *rule_ptr);
    bool        verifyPortMapping(gatewayInfo *deviceInfo, upnpRule *rule_ptr);
    bool        deletePortMapping(gatewayInfo *deviceInfo, upnpRule *rule_ptr);
    bool        applyActionOnSpecificPortMapping(SOAPAction *soapAction, gatewayInfo *deviceInfo, upnpRule *rule_ptr);
    void        removeAllPortMappingsFromIGD();
    //char*       ipAddressToCharArr(IPAddress ipAddress);  // ?? not sure this is needed
    void        upnpRuleToString(upnpRule *rule_ptr);
    String      getSpacesString(int num);
    IPAddress   getHost(String url);
    int         getPort(String url);
    String      getPath(String url);
    String      getTagContent(const String &line, String tagName);

    /* members */
    upnpRuleNode*   _headRuleNode;
    unsigned long   _lastUpdateTime;
    unsigned long   _timeoutMs;  // 0 for blocking operation

    EthernetUDP     _udpClient;
    EthernetClient  _UPnPClient;

    gatewayInfo     _gwInfo;
    unsigned long   _consequtiveFails;
};

#include "UPnP_Generic_Impl.h"

#endif    // UPnP_Generic_Ethernet_h
