/****************************************************************************************************************************
  defines.h
  
  For all Generic boards such as ESP8266, ESP32, WT32_ETH01, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1,Teensy, Portenta_H7
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00, ENC28J60, Native-Ethernet, Portenta Ethernet/WiFi
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under GPL-3.0 license
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#define DEBUG_WIFI_WEBSERVER_PORT   Serial

// Debug Level from 0 to 4
#define _WIFI_LOGLEVEL_             1
#define _WIFININA_LOGLEVEL_         1

#define _DDNS_GENERIC_LOGLEVEL_     1
#define _UPNP_LOGLEVEL_             2

// Select DDNS_USING_WIFI for boards using built-in WiFi, such as Nano-33-IoT
#define DDNS_USING_WIFI             true
#define DDNS_USING_ETHERNET         false

#define USE_WIFI_NINA         true
//#define USE_WIFI_NINA         false

// If not USE_WIFI_NINA, you can USE_WIFI_CUSTOM, then include the custom WiFi library here 
#define USE_WIFI_CUSTOM       false

#if (USE_WIFI_NINA)
  #warning Using WiFiNINA with WiFiNINA_Generic library
  #define SHIELD_TYPE           "WiFiNINA using WiFiNINA_Generic Library"
#elif (!USE_WIFI_NINA && USE_WIFI_CUSTOM)
  //#include "WiFi_XYZ.h"
  #warning Using Custom WiFi_XYZ library
  #define SHIELD_TYPE           "Custom WiFi using WiFi_XYZ Library"
  #include "WiFiEspAT.h"
#endif


#if ( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || \
      defined(ARDUINO_GENERIC_RP2040) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) )
  #if defined(WIFI_USE_RP2040)
    #undef WIFI_USE_RP2040
  #endif
  #define WIFI_USE_RP2040          true
#else
  #error This code is intended to run on the RP2040 platform! Please check your Tools->Board setting.  
#endif

#if defined(WIFI_USE_RP2040) && defined(ARDUINO_ARCH_MBED)

  #warning Using ARDUINO_ARCH_MBED
  
  #if ( defined(ARDUINO_NANO_RP2040_CONNECT)    || defined(ARDUINO_RASPBERRY_PI_PICO) || \
        defined(ARDUINO_GENERIC_RP2040) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) )
    // Only undef known BOARD_NAME to use better one
    #undef BOARD_NAME
  #endif
  
  #if defined(ARDUINO_RASPBERRY_PI_PICO)
    #define BOARD_NAME      "MBED RASPBERRY_PI_PICO"
  #elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
    #define BOARD_NAME      "MBED ADAFRUIT_FEATHER_RP2040"
  #elif defined(ARDUINO_GENERIC_RP2040)
    #define BOARD_NAME      "MBED GENERIC_RP2040"
  #elif defined(ARDUINO_NANO_RP2040_CONNECT) 
    #define BOARD_NAME      "MBED NANO_RP2040_CONNECT"
  #else
    // Use default BOARD_NAME if exists
    #if !defined(BOARD_NAME)
      #define BOARD_NAME      "MBED Unknown RP2040"
    #endif
  #endif

#endif

#ifndef BOARD_NAME
  #ifdef ARDUINO_BOARD
    #define BOARD_NAME          ARDUINO_BOARD
  #else
    #define BOARD_NAME          BOARD_TYPE
  #endif
#endif

#ifndef SHIELD_TYPE
  #define SHIELD_TYPE           "Unknown shield"
#endif

#include <WiFiWebServer.h>
#include <DDNS_Generic.h>

char ssid[] = "****";        // your network SSID (name)
char pass[] = "****";        // your network password

#endif    //defines_h
