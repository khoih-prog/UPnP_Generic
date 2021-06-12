/****************************************************************************************************************************
  PWM_LEDServer_ESP32.ino
  
  For all Generic boards such as ESP8266, ESP32, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00 Ethernet shields
  
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
        You can access this WebServer by either localIP:LISTEN_PORT such as 192.169.2.100:5933/?percentage=20
        or DDNS_Host:LISTEN_PORT, such as account.duckdns.org:5933/?percentage=20
*/

#if !defined(ESP32)
  #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting. 
#endif

// Debug Level from 0 to 4
#define _DDNS_GENERIC_LOGLEVEL_     1
#define _UPNP_LOGLEVEL_             2

// Select DDNS_USING_WIFI for boards using built-in WiFi, such as Nano-33-IoT
#define DDNS_USING_WIFI             true
#define DDNS_USING_ETHERNET         false

#include <WebServer.h>

#include <UPnP_Generic.h>           // https://github.com/khoih-prog/UPnP_Generic

#include <DDNS_Generic.h>           // https://github.com/khoih-prog/DDNS_Generic

const char* ssid      = "your_ssid";
const char* password  = "12345678";

#define LISTEN_PORT         5933
#define LEASE_DURATION      36000                   // seconds
#define FRIENDLY_NAME       ARDUINO_BOARD "-WIFI"   // this name will appear in your router port forwarding section

UPnP* uPnP;

WebServer server(LISTEN_PORT);

// setting PWM properties
const int freq        = 5000;
const int ledChannel  = 0;
const int resolution  = 10; //Resolution 8, 10, 12, 15 bits. Select 10 => 1024 steps

#define LED_REVERSED      false
#define LED_ON            100
#define LED_OFF           0

#define LED_PIN           2     // LED_BUILTIN

const int delayval = 10;

void onUpdateCallback(const char* oldIP, const char* newIP)
{
  (void) oldIP;
  
  Serial.print(F("DDNSGeneric - IP Change Detected: "));
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

  ledcWrite(ledChannel, pwm_val);
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

  message += String(ARDUINO_BOARD);
  message += F(" running UPnP_Generic & DDNS_Generic\n");
  
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

#if ( ARDUINO_ESP32S2_DEV || ARDUINO_FEATHERS2 || ARDUINO_ESP32S2_THING_PLUS || ARDUINO_MICROS2 || \
        ARDUINO_METRO_ESP32S2 || ARDUINO_MAGTAG29_ESP32S2 || ARDUINO_FUNHOUSE_ESP32S2 || \
        ARDUINO_ADAFRUIT_FEATHER_ESP32S2_NOPSRAM )
  #warning Using ESP32_S2
  
  delay(2000);
#endif

  Serial.print("\nStart PWM_LEDServer_ESP32 on "); Serial.println(ARDUINO_BOARD);
  Serial.println(UPNP_GENERIC_VERSION);

  pinMode(LED_PIN,OUTPUT);
  
  // configure LED PWM function
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the LED_PIN
  ledcAttachPin(LED_PIN, ledChannel);

  showLED();

  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

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
  Serial.print(F(", port = "));
  Serial.println(LISTEN_PORT);

  Serial.print(F("Gateway Address: "));
  Serial.println(WiFi.gatewayIP());
  Serial.print(F("Network Mask: "));
  Serial.println(WiFi.subnetMask());
}

void loop(void) 
{
  //delay(100);
  
  DDNSGeneric.update(555000);

  uPnP->updatePortMappings(600000);  // 10 minutes

  server.handleClient();
}
