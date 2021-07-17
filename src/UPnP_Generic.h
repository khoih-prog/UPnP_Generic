/****************************************************************************************************************************
  UPnP_Generic.h
  
  For all Generic boards such as ESP8266, ESP32, WT32_ETH01, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1,Teensy
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00, ENC28J60, Native Ethernet shields
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under GPL-3.0 license
  Version: 3.3.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  3.1.4  K Hoang      23/09/2020 Initial coding for Generic boards using many WiFi/Ethernet modules/shields.
  3.1.5  K Hoang      28/09/2020 Fix issue with nRF52 and STM32F/L/H/G/WB/MP1 using ESP8266/ESP32-AT
  3.2.0  K Hoang      11/06/2021 Add support to RP2040-based boards using ESP-AT, WiFiNINA, W5x00 / ENC28J60
  3.3.0  K Hoang      16/07/2021 Add support to WT32_ETH01 (ESP32 + LAN8720)
 *****************************************************************************************************************************/

#ifndef UPnP_Generic_h
#define UPnP_Generic_h

#include "UPnP_Generic_Debug.h"

#define UPNP_GENERIC_VERSION      "UPnP_Generic v3.3.0"

#if UPNP_USING_ETHERNET
  #include "UPnP_Generic_Ethernet.h"
#elif (ESP8266 || ESP32 || UPNP_USING_WIFI || UPNP_USING_WT32_ETH01)
  #include "UPnP_Generic_WiFi.h"
#endif

#endif    // UPnP_Generic_h
