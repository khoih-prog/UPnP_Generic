/****************************************************************************************************************************
  UPnP_Generic_Debug.h
  
  For all Generic boards such as ESP8266, ESP32, WT32_ETH01, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1,Teensy, Portenta_H7
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00, ENC28J60, Native-Ethernet, Portenta Ethernet/WiFi
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under GPL-3.0 license
  Version: 3.4.1
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  3.1.4  K Hoang      23/09/2020 Initial coding for Generic boards using many WiFi/Ethernet modules/shields.
  3.1.5  K Hoang      28/09/2020 Fix issue with nRF52 and STM32F/L/H/G/WB/MP1 using ESP8266/ESP32-AT
  3.2.0  K Hoang      11/06/2021 Add support to RP2040-based boards using ESP-AT, WiFiNINA, W5x00 / ENC28J60
  3.3.0  K Hoang      16/07/2021 Add support to WT32_ETH01 (ESP32 + LAN8720)
  3.4.0  K Hoang      16/09/2021 Add support to Portenta_H7, using either WiFi or Vision-shield Ethernet
  3.4.1  K Hoang      12/10/2021 Update `platform.ini` and `library.json`
 *****************************************************************************************************************************/

#ifndef UPnP_Generic_Debug_H
#define UPnP_Generic_Debug_H

#include <stdio.h>

#ifdef DEBUG_UPNP_PORT
  #define UPNP_DBG_PORT     DEBUG_UPNP_PORT
#else
  #define UPNP_DBG_PORT     Serial
#endif

// Change _UPNP_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _UPNP_LOGLEVEL_
  #define _UPNP_LOGLEVEL_       0
#endif

///////////////////////////////////////

const char UPNP_MARK[]  = "[UPnP] ";
const char UPNP_SP[]    = " ";

#define UPNP_PRINT          UPNP_DBG_PORT.print
#define UPNP_PRINTLN        UPNP_DBG_PORT.println
#define UPNP_FLUSH          UPNP_DBG_PORT.flush

#define UPNP_PRINT_MARK     UPNP_PRINT(UPNP_MARK)
#define UPNP_PRINT_SP       UPNP_PRINT(UPNP_SP)

///////////////////////////////////////

#define UPNP_LOGERROR(x)         if(_UPNP_LOGLEVEL_>0) { UPNP_PRINT_MARK; UPNP_PRINTLN(x); }
#define UPNP_LOGERROR0(x)        if(_UPNP_LOGLEVEL_>0) { UPNP_PRINT(x); }
#define UPNP_LOGERROR1(x,y)      if(_UPNP_LOGLEVEL_>0) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINTLN(y); }
#define UPNP_LOGERROR2(x,y,z)    if(_UPNP_LOGLEVEL_>0) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINT(y); UPNP_PRINT_SP; UPNP_PRINTLN(z); }
#define UPNP_LOGERROR3(x,y,z,w)  if(_UPNP_LOGLEVEL_>0) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINT(y); UPNP_PRINT_SP; UPNP_PRINT(z); UPNP_PRINT_SP; UPNP_PRINTLN(w); }

///////////////////////////////////////

#define UPNP_LOGWARN(x)          if(_UPNP_LOGLEVEL_>1) { UPNP_PRINT_MARK; UPNP_PRINTLN(x); }
#define UPNP_LOGWARN0(x)         if(_UPNP_LOGLEVEL_>1) { UPNP_PRINT(x); }
#define UPNP_LOGWARN1(x,y)       if(_UPNP_LOGLEVEL_>1) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINTLN(y); }
#define UPNP_LOGWARN2(x,y,z)     if(_UPNP_LOGLEVEL_>1) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINT(y); UPNP_PRINT_SP; UPNP_PRINTLN(z); }
#define UPNP_LOGWARN3(x,y,z,w)   if(_UPNP_LOGLEVEL_>1) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINT(y); UPNP_PRINT_SP; UPNP_PRINT(z); UPNP_PRINT_SP; UPNP_PRINTLN(w); }

///////////////////////////////////////

#define UPNP_LOGINFO(x)          if(_UPNP_LOGLEVEL_>2) { UPNP_PRINT_MARK; UPNP_PRINTLN(x); }
#define UPNP_LOGINFO0(x)         if(_UPNP_LOGLEVEL_>2) { UPNP_PRINT(x); }
#define UPNP_LOGINFO1(x,y)       if(_UPNP_LOGLEVEL_>2) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINTLN(y); }
#define UPNP_LOGINFO2(x,y,z)     if(_UPNP_LOGLEVEL_>2) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINT(y); UPNP_PRINT_SP; UPNP_PRINTLN(z); }
#define UPNP_LOGINFO3(x,y,z,w)   if(_UPNP_LOGLEVEL_>2) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINT(y); UPNP_PRINT_SP; UPNP_PRINT(z); UPNP_PRINT_SP; UPNP_PRINTLN(w); }

///////////////////////////////////////

#define UPNP_LOGDEBUG(x)         if(_UPNP_LOGLEVEL_>3) { UPNP_PRINT_MARK; UPNP_PRINTLN(x); }
#define UPNP_LOGDEBUG0(x)        if(_UPNP_LOGLEVEL_>3) { UPNP_PRINT(x); }
#define UPNP_LOGDEBUG1(x,y)      if(_UPNP_LOGLEVEL_>3) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINTLN(y); }
#define UPNP_LOGDEBUG2(x,y,z)    if(_UPNP_LOGLEVEL_>3) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINT(y); UPNP_PRINT_SP; UPNP_PRINTLN(z); }
#define UPNP_LOGDEBUG3(x,y,z,w)  if(_UPNP_LOGLEVEL_>3) { UPNP_PRINT_MARK; UPNP_PRINT(x); UPNP_PRINT_SP; UPNP_PRINT(y); UPNP_PRINT_SP; UPNP_PRINT(z); UPNP_PRINT_SP; UPNP_PRINTLN(w); }

#endif    // UPnP_Generic_Debug_H
