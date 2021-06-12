/****************************************************************************************************************************
  nRF52_SimpleServer.ino
  
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
        You can access this WebServer by either localIP:LISTEN_PORT such as 192.169.2.100:5952
        or DDNS_Host:LISTEN_PORT, such as account.duckdns.org:5952
*/

#include "defines.h"

#define UPNP_USING_ETHERNET     true

#include <UPnP_Generic.h>

#define LISTEN_PORT         5952
#define LEASE_DURATION      36000  // seconds
#define FRIENDLY_NAME       "RP2040-W5X00"  // this name will appear in your router port forwarding section

UPnP* uPnP;

EthernetWebServer server(LISTEN_PORT);

#if defined(LED_BLUE)
  #define LED_PIN           LED_BLUE        //  BLUE_LED on nRF52840 Feather Express, Itsy-Bitsy
#else
  #define LED_PIN           3               //  RED LED
#endif

const int led = LED_PIN;

void onUpdateCallback(const char* oldIP, const char* newIP)
{
  Serial.print(F("DDNSGeneric - IP Change Detected: "));
  Serial.println(newIP);
}

void handleRoot()
{
#define BUFFER_SIZE     400
  
  digitalWrite(led, 1);
  char temp[BUFFER_SIZE];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  int day = hr / 24;

  hr = hr % 24;

  snprintf(temp, BUFFER_SIZE - 1,
           "<html>\
<head>\
<meta http-equiv='refresh' content='5'/>\
<title>%s</title>\
<style>\
body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
</style>\
</head>\
<body>\
<h1>Hello from %s</h1>\
<h3>running UPnP_Generic & DDNS_Generic</h3>\
<h3>on %s</h3>\
<p>Uptime: %d d %02d:%02d:%02d</p>\
</body>\
</html>", BOARD_NAME, BOARD_NAME, SHIELD_TYPE, day, hr, min % 60, sec % 60);

  server.send(200, F("text/html"), temp);
  digitalWrite(led, 0);
}

void handleNotFound() 
{
  digitalWrite(led, 1);
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
  digitalWrite(led, 0);
}

void setup(void) 
{
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart RP2040_SimpleServer on "); Serial.print(BOARD_NAME);
  Serial.print(" using "); Serial.println(SHIELD_TYPE);
  Serial.println(UPNP_GENERIC_VERSION);
  
  ET_LOGERROR3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);

  Serial.println(F("Default SPI pinout:"));
  Serial.print(F("MOSI:")); Serial.println(MOSI);
  Serial.print(F("MISO:")); Serial.println(MISO);
  Serial.print(F("SCK:"));  Serial.println(SCK);
  Serial.print(F("SS:"));   Serial.println(SS);
  Serial.println(F("========================="));
      
#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // For other boards, to change if necessary
  pinMode(USE_THIS_SS_PIN, OUTPUT);
  digitalWrite(USE_THIS_SS_PIN, HIGH);
  
  // ETHERNET_USE_RPIPICO, use default SS = 5 or 17
  #ifndef USE_THIS_SS_PIN
    #if defined(ARDUINO_ARCH_MBED)
      #define USE_THIS_SS_PIN   5     // For Arduino Mbed core
    #else  
      #define USE_THIS_SS_PIN   17    // For E.Philhower core
    #endif
  #endif

  ET_LOGWARN1(F("RPIPICO setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // For RPI Pico using Arduino Mbed RP2040 core
    // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
    // For RPI Pico using E. Philhower RP2040 core
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
    // Default pin 5/17 to SS/CS
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_ETHERNET3
    // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
    #ifndef ETHERNET3_MAX_SOCK_NUM
      #define ETHERNET3_MAX_SOCK_NUM      4
    #endif
  
    Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
    
  #endif    //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )
#endif

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  IPAddress localIP = Ethernet.localIP();

  Serial.print(F("Using mac index = "));
  Serial.println(index);

  Serial.print(F("Connected! IP address: "));
  Serial.println(localIP);

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

  uPnP = new UPnP(60000);  // -1 means blocking, preferably, use a timeout value (ms)

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
}

void loop(void) 
{
  DDNSGeneric.update(300000);

  uPnP->updatePortMappings(600000);  // 10 minutes

  server.handleClient();
}
