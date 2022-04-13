/****************************************************************************************************************************
  multiFileProject.h
  For all Generic boards such as ESP8266, ESP32, WT32_ETH01, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1,Teensy, Portenta_H7
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00, ENC28J60, Native-Ethernet, Portenta Ethernet/WiFi
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under GPL-3.0 license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#pragma once

// Select DDNS_USING_WIFI for boards using built-in WiFi, such as Nano-33-IoT
#define DDNS_USING_WIFI             false
#define DDNS_USING_ETHERNET         true

#define UPNP_USING_ETHERNET         true

// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
// You can define here or customize for each board at same place with BOARD_TYPE
// Check @ defined(SEEED_XIAO_M0)
//#define USE_THIS_SS_PIN   22  //21  //5 //4 //2 //15

  // Only one if the following to be true
  #define USE_ETHERNET_GENERIC  true
  #define USE_ETHERNET_ESP8266  false 
  #define USE_ETHERNET_ENC      false
  #define USE_UIP_ETHERNET      false
  #define USE_CUSTOM_ETHERNET   false
    
    ////////////////////////////
    
#if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC || USE_UIP_ETHERNET )
  #ifdef USE_CUSTOM_ETHERNET
    #undef USE_CUSTOM_ETHERNET
  #endif
  #define USE_CUSTOM_ETHERNET   false
#endif

#if USE_ETHERNET_GENERIC

  #define SHIELD_TYPE           "W5x00 using Ethernet_Generic Library on SPI0/SPI"

  #define ETHERNET_LARGE_BUFFERS

  #define _ETG_LOGLEVEL_                      1
  
  #include "Ethernet_Generic.hpp"
  #warning Using Ethernet_Generic lib

#elif USE_ETHERNET_ENC
  #include "EthernetENC.h"
  #warning Using EthernetENC lib
  #define SHIELD_TYPE           "ENC28J60 using EthernetENC Library"
  
#elif USE_CUSTOM_ETHERNET
  //#include "Ethernet_XYZ.h"
  #include "Ethernet.h"
  #warning Using Custom Ethernet library. You must include a library and initialize.
  #define SHIELD_TYPE           "Custom Ethernet using Ethernet Library"
  
#elif USE_UIP_ETHERNET
    #include "UIPEthernet.h"
    #warning Using UIPEthernet library
    #define SHIELD_TYPE           "ENC28J60 using UIPEthernet Library"  
    
#else
  #ifdef USE_ETHERNET_GENERIC
    #undef USE_ETHERNET_GENERIC
  #endif  
  #define USE_ETHERNET_GENERIC   true
  
  #include "Ethernet_Generic.h"
  #warning Using default Ethernet_Generic lib
  #define SHIELD_TYPE           "W5x00 using default Ethernet_Generic Library"

// Ethernet_Shield_W5200, EtherCard, EtherSia not supported
// Select just 1 of the following #include if uncomment #define USE_CUSTOM_ETHERNET
// Otherwise, standard Ethernet library will be used for W5x00
  
  ////////////////////////////

#endif      // #if USE_ETHERNET_GENERIC

/////////////////////////////////

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include <UPnP_Generic.hpp>          // https://github.com/khoih-prog/UPnP_Generic
