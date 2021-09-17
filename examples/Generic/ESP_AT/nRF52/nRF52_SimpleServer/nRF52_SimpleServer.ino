/****************************************************************************************************************************
  nRF52_SimpleServer.ino
  
  For all Generic boards such as ESP8266, ESP32, WT32_ETH01, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1,Teensy, Portenta_H7
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00, ENC28J60, Native-Ethernet, Portenta Ethernet/WiFi
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under GPL-3.0 license
 *****************************************************************************************************************************/
/*
  Note: This example includes the library EasyDDNS. You'll have to add this package using your Arduino Library Manager.
        The purpose of this package is to publish your dynamic IP to a DDNS service that will allocate a human readable
        address to your current IP. If you do not need that, you can remove this dependency.
*/

#include "defines.h"

#define UPNP_USING_ETHERNET     false
#define UPNP_USING_WIFI         true

#include <UPnP_Generic.h>

#define LISTEN_PORT         7052
#define LEASE_DURATION      36000  // seconds
#define FRIENDLY_NAME       "NRF52-WIFI-ESPAT"  // this name will appear in your router port forwarding section

UPnP* uPnP;

ESP8266_AT_WebServer *server;

#if defined(LED_BLUE)
  #define LED_PIN           LED_BLUE        //  BLUE_LED on nRF52840 Feather Express, Itsy-Bitsy
#else
  #define LED_PIN           3               //  RED LED
#endif

const int led = LED_PIN;

int status    = WL_IDLE_STATUS;     // the Wifi radio's status

void onUpdateCallback(const char* oldIP, const char* newIP)
{
  Serial.print(F("DDNSGeneric - IP Change Detected: oldIP = "));
  Serial.print(oldIP);
  Serial.print(F(", newIP = "));
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

  server->send(200, F("text/html"), temp);
  digitalWrite(led, 0);
}

void handleNotFound() 
{
  digitalWrite(led, 1);
  String message = F("File Not Found\n\n");
  
  message += F("URI: ");
  message += server->uri();
  message += F("\nMethod: ");
  message += (server->method() == HTTP_GET) ? F("GET") : F("POST");
  message += F("\nArguments: ");
  message += server->args();
  message += F("\n");
  
  for (uint8_t i = 0; i < server->args(); i++) 
  {
    message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
  }
  
  server->send(404, F("text/plain"), message);
  digitalWrite(led, 0);
}

void setup(void) 
{
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart nRF52_SimpleServer on "); Serial.print(BOARD_NAME);
  Serial.print(" using "); Serial.println(SHIELD_TYPE);
  Serial.println(UPNP_GENERIC_VERSION);

  // initialize serial for ESP module
  EspSerial.begin(115200);
  // initialize ESP module
  WiFi.init(&EspSerial);

  Serial.println(F("WiFi shield init done"));

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
  }

  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  
  WiFi.begin(ssid, pass);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(F("."));
  }
  
  Serial.println();

  IPAddress localIP = WiFi.localIP();
  
  Serial.print(F("IP address: "));
  Serial.println(localIP);

  //Serial.print(F("Gateway IP : "));
  //Serial.println(WiFi.gatewayIP());
  
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

  server = new ESP8266_AT_WebServer(LISTEN_PORT);

  if (server)
  {
    server->on(F("/"), handleRoot);
  
    server->on(F("/inline"), []()
    {
      server->send(200, F("text/plain"), F("This works as well"));
    });
  
    server->onNotFound(handleNotFound);
  
    server->begin();
  
    Serial.print(F("HTTP WiFi_ESPAT_WebServer is @ IP : "));
    Serial.print(localIP); 
    Serial.print(F(", port = "));
    Serial.println(LISTEN_PORT);
  }
}

void loop(void) 
{
  DDNSGeneric.update(555000);

  uPnP->updatePortMappings(600000);  // 10 minutes

  if (server)
    server->handleClient();
}
