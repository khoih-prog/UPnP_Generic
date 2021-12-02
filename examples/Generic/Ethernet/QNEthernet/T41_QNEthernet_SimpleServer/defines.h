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
#define _UPNP_LOGLEVEL_             3

// Select DDNS_USING_WIFI for boards using built-in WiFi, such as Nano-33-IoT
#define DDNS_USING_WIFI             false
#define DDNS_USING_ETHERNET         true

/////////////////////////////////

#if ( defined(CORE_TEENSY) && defined(__IMXRT1062__) && defined(ARDUINO_TEENSY41) ) 
  // For Teensy 4.1
  #define BOARD_NAME      "TEENSY 4.1"
  // Use true for NativeEthernet Library, false if using other Ethernet libraries
  #define USE_NATIVE_ETHERNET     false
  #define USE_QN_ETHERNET         true

  #include "QNEthernet.h"       // https://github.com/ssilverman/QNEthernet
  using namespace qindesign::network;
  #warning Using QNEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error

  #define USE_ETHERNET_WRAPPER      false
  
#else
  #error Only Teensy 4.1 supported
#endif


/////////////////////////////////

#include "QNEthernet.h"       // https://github.com/ssilverman/QNEthernet
#warning Using Portenta_Ethernet lib for Portenta_H7.
#define SHIELD_TYPE           "QNEthernet"

/////////////////////////////////

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       2

#include <EthernetWebServer.h>

#include <DDNS_Generic.h>

/////////////////////////////////

#endif    //defines_h
