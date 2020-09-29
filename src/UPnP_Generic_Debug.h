/****************************************************************************************************************************
  UPnP_Generic_Debug.h
  
  For all Generic boards such as ESP8266, ESP32, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266-AT, W5x00 Ethernet shields
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under MIT license
  Version: 3.1.5
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  3.1.4  K Hoang      23/09/2020 Initial coding for Generic boards using many WiFi/Ethernet modules/shields.
  3.1.5  K Hoang      28/09/2020 Fix issue with nRF52 and STM32F/L/H/G/WB/MP1 using ESP8266/ESP32-AT
 *****************************************************************************************************************************/

#ifndef UPnP_Generic_Debug_H
#define UPnP_Generic_Debug_H

#include <stdio.h>

#ifdef DEBUG_UPNP_PORT
  #define UPNP_DBG_OUTPUT DEBUG_UPNP_PORT
#else
  #define UPNP_DBG_OUTPUT Serial
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

#define UPNP_FLUSH()            { UPNP_DBG_OUTPUT.flush(); }

///////////////////////////////////////

#define UPNP_LOGERROR(x)         if(_UPNP_LOGLEVEL_>0) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.println(x); }
#define UPNP_LOGERROR0(x)        if(_UPNP_LOGLEVEL_>0) { UPNP_DBG_OUTPUT.print(x); }
#define UPNP_LOGERROR1(x,y)      if(_UPNP_LOGLEVEL_>0) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(y); }
#define UPNP_LOGERROR2(x,y,z)    if(_UPNP_LOGLEVEL_>0) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(y); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(z); }
#define UPNP_LOGERROR3(x,y,z,w)  if(_UPNP_LOGLEVEL_>0) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(y); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(z); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(w); }

///////////////////////////////////////

#define UPNP_LOGWARN(x)          if(_UPNP_LOGLEVEL_>1) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.println(x); }
#define UPNP_LOGWARN0(x)         if(_UPNP_LOGLEVEL_>1) { UPNP_DBG_OUTPUT.print(x); }
#define UPNP_LOGWARN1(x,y)       if(_UPNP_LOGLEVEL_>1) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(y); }
#define UPNP_LOGWARN2(x,y,z)     if(_UPNP_LOGLEVEL_>1) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(y); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(z); }
#define UPNP_LOGWARN3(x,y,z,w)   if(_UPNP_LOGLEVEL_>1) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(y); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(z); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(w); }

///////////////////////////////////////

#define UPNP_LOGINFO(x)          if(_UPNP_LOGLEVEL_>2) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.println(x); }
#define UPNP_LOGINFO0(x)         if(_UPNP_LOGLEVEL_>2) { UPNP_DBG_OUTPUT.print(x); }
#define UPNP_LOGINFO1(x,y)       if(_UPNP_LOGLEVEL_>2) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(y); }
#define UPNP_LOGINFO2(x,y,z)     if(_UPNP_LOGLEVEL_>2) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(y); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(z); }
#define UPNP_LOGINFO3(x,y,z,w)   if(_UPNP_LOGLEVEL_>2) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(y); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(z); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(w); }

///////////////////////////////////////

#define UPNP_LOGDEBUG(x)         if(_UPNP_LOGLEVEL_>3) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.println(x); }
#define UPNP_LOGDEBUG0(x)        if(_UPNP_LOGLEVEL_>3) { UPNP_DBG_OUTPUT.print(x); }
#define UPNP_LOGDEBUG1(x,y)      if(_UPNP_LOGLEVEL_>3) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(y); }
#define UPNP_LOGDEBUG2(x,y,z)    if(_UPNP_LOGLEVEL_>3) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(y); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(z); }
#define UPNP_LOGDEBUG3(x,y,z,w)  if(_UPNP_LOGLEVEL_>3) { UPNP_DBG_OUTPUT.print("[UPnP] "); UPNP_DBG_OUTPUT.print(x); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(y); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.print(z); UPNP_DBG_OUTPUT.print(" "); UPNP_DBG_OUTPUT.println(w); }

#endif    // UPnP_Generic_Debug_H
