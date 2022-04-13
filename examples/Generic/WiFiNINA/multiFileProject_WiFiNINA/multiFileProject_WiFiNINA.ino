/****************************************************************************************************************************
  multiFileProject_WiFiNINA.ino
  For all Generic boards such as ESP8266, ESP32, WT32_ETH01, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1,Teensy, Portenta_H7
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00, ENC28J60, Native-Ethernet, Portenta Ethernet/WiFi
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under GPL-3.0 license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#define UPNP_GENERIC_VERSION_MIN_TARGET      "UPnP_Generic v3.5.0"
#define UPNP_GENERIC_VERSION_MIN             3005000

#include "multiFileProject.h"

#include <DDNS_Generic.h>

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <UPnP_Generic.h>          // https://github.com/khoih-prog/UPnP_Generic

void setup() 
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  delay(500);
  
  Serial.println("\nStart multiFileProject_WiFiNINA");
  Serial.println(UPNP_GENERIC_VERSION);

#if defined(UPNP_GENERIC_VERSION_MIN)
  if (UPNP_GENERIC_VERSION_INT < UPNP_GENERIC_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(UPNP_GENERIC_VERSION_MIN_TARGET);
  }
#endif

  Serial.print("You're OK now");
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
