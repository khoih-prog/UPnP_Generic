/****************************************************************************************************************************
  STM32_PWM_LEDServer.ino
  
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
        You can access this WebServer by either localIP:LISTEN_PORT such as 192.169.2.100:6033/?percentage=20
        or DDNS_Host:LISTEN_PORT, such as account.duckdns.org:6033/?percentage=20
*/

#include "defines.h"

#define UPNP_USING_ETHERNET     true

#include <UPnP_Generic.h>

#define LISTEN_PORT         6033
#define LEASE_DURATION      36000  // seconds
#define FRIENDLY_NAME       "STM32-LED-W5X00"  // this name will appear in your router port forwarding section

UPnP* uPnP;

EthernetWebServer server(LISTEN_PORT);

#define LED_REVERSED      false
#define LED_ON            0
#define LED_OFF           100

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

  Serial.print("\nStart STM32_PWM_LEDServer on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));

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

    Serial.println("\nUPnP done");
  }

  showLED();

  server.on("/", handleRoot);

  server.on("/inline", []() 
  {
    server.send(200, "text/plain", "This works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  
  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
  Serial.print(localIP); 
  Serial.print(", port = ");
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
