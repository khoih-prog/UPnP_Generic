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

// Debug Level from 0 to 4
#define _DDNS_GENERIC_LOGLEVEL_     1
#define _UPNP_LOGLEVEL_             2

// Select DDNS_USING_WIFI for boards using built-in WiFi, such as Nano-33-IoT
#define DDNS_USING_WIFI             false
#define DDNS_USING_ETHERNET         true

/////////////////////////////////

#if ( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || \
      defined(ARDUINO_GENERIC_RP2040) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) )
  #if defined(ETHERNET_USE_RP2040)
    #undef ETHERNET_USE_RP2040
  #endif
  #define ETHERNET_USE_RP2040          true
  #warning Use RP2040 architecture with Ethernet  
#else
  #error This code is intended to run on the RP2040 platform! Please check your Tools->Board setting.  
#endif
  

/////////////////////////////////

#if ETHERNET_USE_RP2040
  
  // Default pin 5 (in Mbed) or 17 to SS/CS
  #if defined(ARDUINO_ARCH_MBED)
    // For RPI Pico using Arduino Mbed RP2040 core
    // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
    
    #define USE_THIS_SS_PIN       5

    #if defined(BOARD_NAME)
      #undef BOARD_NAME
    #endif

    #if defined(ARDUINO_RASPBERRY_PI_PICO) 
      #define BOARD_TYPE      "MBED RASPBERRY_PI_PICO"
    #elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
      #define BOARD_TYPE      "MBED DAFRUIT_FEATHER_RP2040"
    #elif defined(ARDUINO_GENERIC_RP2040)
      #define BOARD_TYPE      "MBED GENERIC_RP2040"
    #else
      #define BOARD_TYPE      "MBED Unknown RP2040"
    #endif
    
  #else
    // For RPI Pico using E. Philhower RP2040 core
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
    #define USE_THIS_SS_PIN       17

  #endif
    
  #define SS_PIN_DEFAULT        USE_THIS_SS_PIN

  // For RPI Pico
  #warning Use RPI-Pico RP2040 architecture  

#endif

///////////////////////////////////////////
// Select Ethernet Library for the Shield
///////////////////////////////////////////

#define USE_UIP_ETHERNET        false
#define USE_CUSTOM_ETHERNET     false

// Only one if the following to be true
#define USE_ETHERNET            false
#define USE_ETHERNET2           false
#define USE_ETHERNET3           false
#define USE_ETHERNET_LARGE      true
#define USE_ETHERNET_ESP8266    false
#define USE_ETHERNET_ENC        false

#if ( USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE || USE_ETHERNET_ESP8266 || USE_ETHERNET_ENC )
  #ifdef USE_CUSTOM_ETHERNET
    #undef USE_CUSTOM_ETHERNET
    #define USE_CUSTOM_ETHERNET   false //true
  #endif
#endif

// Currently, only Ethernet lib available for STM32 using W5x00
#if !(USE_BUILTIN_ETHERNET || ETHERNET_USE_STM32)
  #if USE_ETHERNET3
    #include "Ethernet3.h"
    #warning Use Ethernet3 lib
    #define SHIELD_TYPE           "W5x00 using Ethernet3 Library"
  #elif USE_ETHERNET2
    #include "Ethernet2.h"
    #warning Use Ethernet2 lib
    #define SHIELD_TYPE           "W5x00 using Ethernet2 Library"
  #elif USE_ETHERNET_LARGE
    #include "EthernetLarge.h"
    #warning Use EthernetLarge lib
    #define SHIELD_TYPE           "W5x00 using EthernetLarge Library"
  #elif USE_ETHERNET_ESP8266
    #include "Ethernet_ESP8266.h"
    #warning Use Ethernet_ESP8266 lib
    #define SHIELD_TYPE           "W5x00 using Ethernet_ESP8266 Library"
  #elif USE_ETHERNET_ENC
    #include "EthernetENC.h"
    #warning Use EthernetENC lib
    #define SHIELD_TYPE           "ENC28J60 using EthernetENC Library"  
  #elif USE_CUSTOM_ETHERNET
    #include "Ethernet_XYZ.h"
    #warning Use Custom Ethernet library from EthernetWrapper. You must include a library here or error.
    #define SHIELD_TYPE           "using Custom Ethernet Library"
  #elif USE_UIP_ETHERNET
    #include "UIPEthernet.h"
    #warning Use UIPEthernet library
    #define SHIELD_TYPE           "ENC28J60 using UIPEthernet Library"
  #else
    #ifdef USE_ETHERNET
      #undef USE_ETHERNET
    #endif
    #define USE_ETHERNET          true
    #include "Ethernet.h"
    #warning Use Ethernet lib
    #define SHIELD_TYPE           "W5x00 using Ethernet Library"
  #endif
#endif

/////////////////////////////////

/////////////////////////////////

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

/////////////////////////////////

#include <EthernetWebServer.h>  
#include <DDNS_Generic.h>

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

// Select the IP address according to your local network
IPAddress ip(192, 168, 2, 222);

/////////////////////////////////

#endif    //defines_h
