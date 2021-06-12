/****************************************************************************************************************************
  defines.h
  
  For all Generic boards such as ESP8266, ESP32, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1,Teensy
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00, ENC28J60, Native Ethernet shields
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under MIT license
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#define DEBUG_ESP8266_AT_WEBSERVER_PORT Serial

// Debug Level from 0 to 4
#define _ESP_AT_LOGLEVEL_           1

#define _DDNS_GENERIC_LOGLEVEL_     1
#define _UPNP_LOGLEVEL_             2

// Select DDNS_USING_WIFI for boards using built-in WiFi, such as Nano-33-IoT
#define DDNS_USING_WIFI             true
#define DDNS_USING_ETHERNET         false

// This must be true here, or error
#define DDNS_USING_WIFI_AT          true

// Uncomment to use ESP32-AT commands
//#define USE_ESP32_AT              true

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
  #if defined(WIFI_USE_STM32)
    #undef WIFI_USE_STM32
  #endif
  #define WIFI_USE_STM32      true
#else
  #error This code is intended to run on the STM32 platform! Please check your Tools->Board setting.  
#endif

// For STM32
#warning EspSerial using SERIAL_PORT_HARDWARE, can be Serial or Serial1. See your board variant.h
#define EspSerial     SERIAL_PORT_HARDWARE    //Serial1

#if defined(STM32F0)
  #warning STM32F0 board selected
  #define BOARD_TYPE  "STM32F0"
#elif defined(STM32F1)
  #warning STM32F1 board selected
  #define BOARD_TYPE  "STM32F1"
#elif defined(STM32F2)
  #warning STM32F2 board selected
  #define BOARD_TYPE  "STM32F2"
#elif defined(STM32F3)
  #warning STM32F3 board selected
  #define BOARD_TYPE  "STM32F3"
#elif defined(STM32F4)
  #warning STM32F4 board selected
  #define BOARD_TYPE  "STM32F4"
#elif defined(STM32F7)

  #if defined(ARDUINO_NUCLEO_F767ZI)
    #warning Nucleo-144 NUCLEO_F767ZI board selected, using HardwareSerial Serial1 @ pin D0/RX and D1/TX
    // RX TX
    HardwareSerial Serial1(D0, D1);
  #else
  
    #warning STM32F7 board selected
    #define BOARD_TYPE  "STM32F7"

  #endif
  
#elif defined(STM32L0)
  #if defined(ARDUINO_NUCLEO_L053R8)
    #warning Nucleo-64 NUCLEO_L053R8 board selected, using HardwareSerial Serial1 @ pin D0/RX and D1/TX
    // RX TX
    HardwareSerial Serial1(D0, D1);   // (PA3, PA2);
  #else
  
    #warning STM32L0 board selected
    #define BOARD_TYPE  "STM32L0"

  #endif
    
#elif defined(STM32L1)
  #warning STM32L1 board selected
  #define BOARD_TYPE  "STM32L1"
#elif defined(STM32L4)
  #warning STM32L4 board selected
  #define BOARD_TYPE  "STM32L4"
#elif defined(STM32H7)
  #warning STM32H7 board selected
  #define BOARD_TYPE  "STM32H7"
#elif defined(STM32G0)
  #warning STM32G0 board selected
  #define BOARD_TYPE  "STM32G0"
#elif defined(STM32G4)
  #warning STM32G4 board selected
  #define BOARD_TYPE  "STM32G4"
#elif defined(STM32WB)
  #warning STM32WB board selected
  #define BOARD_TYPE  "STM32WB"
#elif defined(STM32MP1)
  #warning STM32MP1 board selected
  #define BOARD_TYPE  "STM32MP1"
#else
  #warning STM32 unknown board selected
  #define BOARD_TYPE  "STM32 Unknown"
#endif


#ifndef BOARD_NAME
  #ifdef ARDUINO_BOARD
    #define BOARD_NAME          ARDUINO_BOARD
  #else
    #define BOARD_NAME          BOARD_TYPE
  #endif
#endif

#ifndef SHIELD_TYPE
  #if USE_ESP32_AT
    #define SHIELD_TYPE           "ESP32_AT shield"
  #else
    #define SHIELD_TYPE           "ESP8266_AT shield"
  #endif
#endif

#include <ESP8266_AT_WebServer.h>
#include <ESP8266_AT_Client.h>
#include <ESP8266_AT_Udp.h>

#define WiFiClient    ESP8266_AT_Client
#define WiFiUDP       ESP8266_AT_UDP

#include <DDNS_Generic.h>

char ssid[] = "****";        // your network SSID (name)
char pass[] = "****";        // your network password

#endif    //defines_h
