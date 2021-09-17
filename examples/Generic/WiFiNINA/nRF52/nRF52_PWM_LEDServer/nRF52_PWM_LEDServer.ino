/****************************************************************************************************************************
  nRF52_PWM_LEDServer.ino
  
  For all Generic boards such as ESP8266, ESP32, WT32_ETH01, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1,Teensy, Portenta_H7
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00, ENC28J60, Native-Ethernet, Portenta Ethernet/WiFi
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under GPL-3.0 license
 *****************************************************************************************************************************/
/*
  Note: This example uses the DDNS_Generic library (https://github.com/khoih-prog/DDNS_Generic)
        You can access this WebServer by either localIP:LISTEN_PORT such as 192.169.2.100:6053/?percentage=20
        or DDNS_Host:LISTEN_PORT, such as account.duckdns.org:6053/?percentage=20
*/

#include "defines.h"

#define UPNP_USING_ETHERNET     false
#define UPNP_USING_WIFI         true

#include <UPnP_Generic.h>

#define LISTEN_PORT         6053
#define LEASE_DURATION      36000  // seconds
#define FRIENDLY_NAME       "NRF52-LED-WIFININA"  // this name will appear in your router port forwarding section

UPnP* uPnP;

WiFiWebServer server(LISTEN_PORT);

int status    = WL_IDLE_STATUS;     // the Wifi radio's status

#define LED_REVERSED      false

#if LED_REVERSED
  #define LED_ON          0
  #define LED_OFF         100
#else
  #define LED_ON          100
  #define LED_OFF         0
#endif

#if defined(LED_BLUE)
  #define LED_PIN           LED_BLUE        //  BLUE_LED on nRF52840 Feather Express, Itsy-Bitsy
#else
  #define LED_PIN           3               //  RED LED
#endif

const int delayval = 10;

void onUpdateCallback(const char* oldIP, const char* newIP)
{
  Serial.print(F("DDNSGeneric - IP Change Detected: "));
  Serial.println(newIP);
}

// 0 <= percentage <= 100
void setPower(uint32_t percentage)
{
  long pwm_val = map(percentage, 0, 100, 0, 1023);

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

  Serial.print("\nStart nRF52_PWM_LEDServer on "); Serial.print(BOARD_NAME);
  Serial.print(" using "); Serial.println(SHIELD_TYPE);
  Serial.println(UPNP_GENERIC_VERSION);

  pinMode(LED_PIN,OUTPUT);

  showLED();

  // check for the presence of the shield
#if USE_WIFI_NINA
  if (WiFi.status() == WL_NO_MODULE)
#else
  if (WiFi.status() == WL_NO_SHIELD)
#endif
  {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
  }

#if USE_WIFI_NINA
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println(F("Please upgrade the firmware"));
  }
#endif

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
  
  Serial.print(F("HTTP WiFiWebServer is @ IP : "));
  Serial.print(localIP); 
  Serial.print(", port = ");
  Serial.println(LISTEN_PORT);
}

void loop(void) 
{
  DDNSGeneric.update(300000);

  uPnP->updatePortMappings(600000);  // 10 minutes

  server.handleClient();
}
