/****************************************************************************************************************************
  SAMD_PWM_LEDServer.ino
  
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
/*
  Note: This example uses the DDNS_Generic library (https://github.com/khoih-prog/DDNS_Generic)
        You can access this WebServer by either localIP:LISTEN_PORT such as 192.169.2.100:5991/?percentage=20
        or DDNS_Host:LISTEN_PORT, such as account.duckdns.org:5991/?percentage=20
*/

#include "defines.h"

#define UPNP_USING_ETHERNET     false
#define UPNP_USING_WIFI         true

#include <UPnP_Generic.h>

#define LISTEN_PORT         5991
#define LEASE_DURATION      36000  // seconds
#define FRIENDLY_NAME       "SAMD-LED-WIFI-ESPAT"  // this name will appear in your router port forwarding section

UPnP* uPnP;

ESP8266_AT_WebServer server(LISTEN_PORT);

int status    = WL_IDLE_STATUS;     // the Wifi radio's status

#define LED_REVERSED      false
#define LED_ON            100
#define LED_OFF           0

#define LED_PIN           13     // LED_BUILTIN

const int delayval = 10;

void onUpdateCallback(const char* oldIP, const char* newIP)
{
  Serial.print("DDNSGeneric - IP Change Detected: ");
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
  String message = "Hello from " + String(BOARD_NAME) + " running UPnP_Generic & DDNS_Generic\n";

  message += "Number of args received: ";
  message += server.args();  // get number of parameters
  message += "\n";

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

  server.send(200, "text/plain", message);       //Response to the HTTP request

  setPower(percentage);
}

void handleNotFound()
{
  String message = "File Not Found\n\n";

  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void setup(void) 
{ 
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart SAMD_PWM_LEDServer on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));

  pinMode(LED_PIN,OUTPUT);

  showLED();

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

  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, pass);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");

  IPAddress localIP = WiFi.localIP();
  
  Serial.print("IP address: ");
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

      Serial.println("commitPortMappings result =" + String(result));

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

    Serial.println("\nUPnP done");
  }

  showLED();
  
  server.on("/", handleRoot);

  server.on("/inline", []()
  {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  
  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
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
