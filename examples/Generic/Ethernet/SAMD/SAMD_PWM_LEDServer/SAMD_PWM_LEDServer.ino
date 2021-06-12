/****************************************************************************************************************************
  SAMD_PWM_LEDServer.ino
  
  For all Generic boards such as ESP8266, ESP32, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1,Teensy
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00, ENC28J60, Native Ethernet shields
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under MIT license
  Version: 3.2.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  3.1.4  K Hoang      23/09/2020 Initial coding for Generic boards using many WiFi/Ethernet modules/shields.
  3.1.5  K Hoang      28/09/2020 Fix issue with nRF52 and STM32F/L/H/G/WB/MP1 using ESP8266/ESP32-AT
  3.2.0  K Hoang      11/06/2021 Add support to RP2040-based boards using ESP-AT, WiFiNINA, W5x00 / ENC28J60
 *****************************************************************************************************************************/
/*
  Note: This example uses the DDNS_Generic library (https://github.com/khoih-prog/DDNS_Generic)
        You can access this WebServer by either localIP:LISTEN_PORT such as 192.169.2.100:5991/?percentage=20
        or DDNS_Host:LISTEN_PORT, such as account.duckdns.org:5991/?percentage=20
*/

#include "defines.h"

#define UPNP_USING_ETHERNET     true

#include <UPnP_Generic.h>

#define LISTEN_PORT         5991
#define LEASE_DURATION      36000  // seconds
#define FRIENDLY_NAME       "SAMD-LED-W5X00"  // this name will appear in your router port forwarding section

UPnP* uPnP;

EthernetWebServer server(LISTEN_PORT);

#define LED_REVERSED      false
#define LED_ON            0
#define LED_OFF           100

#define LED_PIN           13     // LED_BUILTIN

const int delayval = 10;

void onUpdateCallback(const char* oldIP, const char* newIP)
{
  Serial.print(F("DDNSGeneric - IP Change Detected: oldIP = "));
  Serial.print(oldIP);
  Serial.print(F(", newIP = "));
  Serial.println(newIP);
}

// 0 <= percentage <= 100
void setPower(uint32_t percentage)
{
  long pwm_val = map(percentage, LED_OFF, LED_ON, 0, 1023);

  if (pwm_val > 1023)
  {
    pwm_val = 1023;
  }

  analogWrite(LED_PIN, pwm_val);
}

void fadeOn(void)
{
#if LED_REVERSED  
  for (int i = 100; i >= 0; i--)
#else  
  for (int i = 0; i < 100; i++)
#endif
  {
    setPower(i);
    delay(delayval);
  }
}

void fadeOff(void)
{
#if LED_REVERSED  
  for (int i = 0; i < 100; i++)
#else  
  for (int i = 100; i >= 0; i--)
#endif  
  {
    setPower(i);
    delay(delayval);
  }
}

void showLED(void)
{
  for (int i = 0; i < 2; i++)
  {  
    fadeOn();
    fadeOff(); 
  }
}
  
void handleRoot()
{
  String message = F("Hello from ");

  message += String(BOARD_NAME);
  message += F(" running UPnP_Generic & DDNS_Generic\n");
  message += F("on ");
  message += String(SHIELD_TYPE);
  message += F("\nNumber of args received: ");
  message += server.args();  // get number of parameters
  message += F("\n");

  int percentage = 0;

  for (int i = 0; i < server.args(); i++)
  {
    message += "Arg #" + (String)i + " => ";
    message += server.argName(i) + ": ";  // get the name of the parameter
    message += server.arg(i) + "\n";  // get the value of the parameter

    if (server.argName(i).equals("percentage"))
    {
      percentage = server.arg(i).toInt();
    }
  }

  server.send(200, F("text/plain"), message);       //Response to the HTTP request

  setPower(percentage);
}

void handleNotFound() 
{
  String message = F("File Not Found\n\n");
  
  message += F("URI: ");
  message += server.uri();
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? F("GET") : F("POST");
  message += F("\nArguments: ");
  message += server.args();
  message += F("\n");
  
  for (uint8_t i = 0; i < server.args(); i++) 
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  
  server.send(404, F("text/plain"), message);
}

void setup(void) 
{
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart SAMD_PWM_LEDServer on "); Serial.print(BOARD_NAME);
  Serial.print(" using "); Serial.println(SHIELD_TYPE);
  Serial.println(UPNP_GENERIC_VERSION);

  pinMode(LED_PIN,OUTPUT);

  showLED();
  
  ET_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);

  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
  ET_LOGWARN(F("========================="));

  #if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
    // For other boards, to change if necessary
    #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2  || USE_ETHERNET_ENC )
      // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
      Ethernet.init (USE_THIS_SS_PIN);
    
    #elif USE_ETHERNET3
      // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
      #ifndef ETHERNET3_MAX_SOCK_NUM
        #define ETHERNET3_MAX_SOCK_NUM      4
      #endif
    
      Ethernet.setCsPin (USE_THIS_SS_PIN);
      Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
  
    #elif USE_CUSTOM_ETHERNET
      // You have to add initialization for your Custom Ethernet here
      // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
      //Ethernet.init(USE_THIS_SS_PIN);
      
    #endif  //( ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2  || USE_ETHERNET_ENC )
  #endif
  
  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  IPAddress localIP = Ethernet.localIP();

  ////////////////

  DDNSGeneric.service("duckdns");    // Enter your DDNS Service Name - "duckdns" / "noip"

  /*
    For DDNS Providers where you get a token:
    DDNSGeneric.client("domain", "token");

    For DDNS Providers where you get username and password: ( Leave the password field empty "" if not required )
    DDNSGeneric.client("domain", "username", "password");
  */
  DDNSGeneric.client("account.duckdns.org", "12345678-1234-1234-1234-123456789012");

  DDNSGeneric.onUpdate(onUpdateCallback);

  ////////////////

  uPnP = new UPnP(30000);  // -1 means blocking, preferably, use a timeout value (ms)

  if (uPnP)
  {
    uPnP->addPortMappingConfig(localIP, LISTEN_PORT, RULE_PROTOCOL_TCP, LEASE_DURATION, FRIENDLY_NAME);

    bool portMappingAdded = false;

#define RETRY_TIMES     4
    int retries = 0;

    while (!portMappingAdded && (retries < RETRY_TIMES))
    {
      Serial.println("Add Port Forwarding, Try # " + String(++retries));

      int result = uPnP->commitPortMappings();

      portMappingAdded = ( (result == PORT_MAP_SUCCESS) || (result == ALREADY_MAPPED) );

      //Serial.println("commitPortMappings result =" + String(result));

      if (!portMappingAdded)
      {
        // for debugging, you can see this in your router too under forwarding or UPnP
        //uPnP->printAllPortMappings();
        //Serial.println(F("This was printed because adding the required port mapping failed"));
        if (retries < RETRY_TIMES)
          delay(10000);  // 10 seconds before trying again
      }
    }

    uPnP->printAllPortMappings();

    Serial.println(F("\nUPnP done"));
  }

  showLED();

  server.on(F("/"), handleRoot);

  server.on(F("/inline"), []()
  {
    server.send(200, F("text/plain"), F("This works as well"));
  });

  server.onNotFound(handleNotFound);

  server.begin();
  
  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
  Serial.print(localIP); 
  Serial.print(F(", port = "));
  Serial.println(LISTEN_PORT);

  Serial.print(F("Gateway Address: "));
  Serial.println(Ethernet.gatewayIP());
  Serial.print(F("Network Mask: "));
  Serial.println(Ethernet.subnetMask());
}

void loop(void) 
{
  //delay(100);
  
  DDNSGeneric.update(300000);

  uPnP->updatePortMappings(600000);  // 10 minutes

  server.handleClient();
}
