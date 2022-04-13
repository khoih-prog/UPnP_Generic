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

#if (defined(ESP32) || defined(ESP8266))
  #error Not for ESP32 and ESP8266
#endif

// Select DDNS_USING_WIFI for boards using built-in WiFi, such as Nano-33-IoT
#define DDNS_USING_WIFI             true
#define DDNS_USING_ETHERNET         false

#define UPNP_USING_WIFI             true

#define USE_WIFI_NINA               true

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiUdp.h>
  #include <WiFiClient.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <WiFiUdp.h>
  #include <WiFiClient.h>
#elif USE_WIFININA
  #include <WiFiNINA_Generic.h>
  #include <WiFiUdp_Generic.h>
#endif

/////////////////////////////////

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include <WiFiWebServer.hpp>          // https://github.com/khoih-prog/WiFiWebServer
#include <UPnP_Generic.hpp>           // https://github.com/khoih-prog/UPnP_Generic
