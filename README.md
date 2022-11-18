## UPnP_Generic Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/UPnP_Generic.svg?)](https://www.ardu-badge.com/UPnP_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/UPnP_Generic.svg)](https://github.com/khoih-prog/UPnP_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/UPnP_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/UPnP_Generic.svg)](http://github.com/khoih-prog/UPnP_Generic/issues)

---
---

## Table of Contents

* [Important Change from v3.5.0](#Important-Change-from-v350)
* [Why do we need this UPnP_Generic library](#why-do-we-need-this-upnp_generic-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported WiFi shields/modules](#currently-supported-wifi-shieldsmodules)
  * [Currently supported Ethernet shields/modules](#currently-supported-ethernet-shieldsmodules)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For RTL8720DN boards using AmebaD core](#10-for-rtl8720dn-boards-using-amebad-core)
  * [11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core](#11-For-SAMD21-and-SAMD51-boards-using-ArduinoCore-fab-sam-core)
  * [12. For Seeeduino RP2040 boards](#12-For-Seeeduino-RP2040-boards)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. For fixing ESP32 compile error](#7-for-fixing-esp32-compile-error)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [Configuration Notes](#configuration-notes)
  * [ 1. How to use built-in WiFi in ESP8266/ESP32](#1-how-to-use-built-in-wifi-in-esp8266esp32)
  * [ 2. How to select which built-in Ethernet or shield to use](#2-how-to-select-which-built-in-ethernet-or-shield-to-use)
  * [ 3. How to select which built-in WiFi or shield to use](#3-how-to-select-which-built-in-wifi-or-shield-to-use)
  * [Important](#important)
  * [ 4. How to select another CS/SS pin to use](#4-how-to-select-another-csss-pin-to-use)
  * [ 5. How to use W5x00 with ESP8266](#5-how-to-use-w5x00-with-esp8266)
  * [ 6. How to increase W5x00 TX/RX buffer](#6-how-to-increase-w5x00-txrx-buffer)
  * [ 7. How to use SPI2 for ESP32 using W5x00 and Ethernet_Generic Library](#7-How-to-use-SPI2-for-ESP32-using-W5x00-and-Ethernet_Generic-Library)
  * [ 8. How to use SPI1 for RP2040 using W5x00 and Ethernet_Generic Library](#8-How-to-use-SPI1-for-RP2040-using-W5x00-and-Ethernet_Generic-Library)
* [HOWTO Usage](#howto-usage)
  * [ 1. Include](#1-include)
  * [ 2. Declare](#2-declare)
  * [ 3. Setup](#3-setup)
  * [ 4. Loop](#4-loop) 
  * [ 5. API](#5-api)
  * [ 6. Print](#6-print)
* [Examples](#examples)
  * [A. For ESP8266 and ESP32 boards](#a-for-esp8266-and-esp32-boards)
  * [B. For Ethernet shields](#b-for-ethernet-shields)
    * [1. nRF52](#1-nrf52)
    * [2. RP2040](#2-rp2040)
    * [3. SAMD](#3-samd)
    * [4. STM32](#4-STM32)
    * [5. PORTENTA_H7](#5-PORTENTA_H7)
    * [6. TEENSY_4.1](#6-TEENSY_41)
    * [7. General](#7-General)
  * [C. For WiFiNINA shields](#c-for-wifinina-shields)
    * [1. nRF52](#1-nrf52-1)
    * [2. RP2040](#2-rp2040-1)
    * [3. SAMD](#3-samd-1)
    * [4. STM32](#4-STM32-1)
    * [5. General](#5-General)
  * [D. For ESP8266-AT/ESP32-AT shields](#d-for-esp8266-atesp32-at-shields)
    * [1. nRF52](#1-nrf52-2)
    * [2. SAMD](#2-samd-2)
    * [3. STM32](#3-STM32-2)
  * [E. For WT32_ETH01 boards](#e-for-wt32_eth01-boards)
  * [F. For WiFi shields](#f-for-wifi-shields)
    * [1. PORTENTA_H7](#1-PORTENTA_H7)
* [Example nRF52_SimpleServer](#example-nrf52_simpleserver)
  * [1. File nRF52_SimpleServer.ino](#1-file-nrf52_simpleserverino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [ 1. SAMD_SimpleServer on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library](#1-samd_simpleserver-on-samd_nano_33_iot-with-wifinina-using-wifinina_generic-library)
  * [ 2. nRF52_SimpleServer on Adafruit NRF52840_FEATHER with W5500 using Ethernet_Generic Library](#2-nrf52_simpleserver-on-adafruit-nrf52840_feather-with-w5500-using-Ethernet_Generic-library)
  * [ 3. nRF52_SimpleServer on Adafruit NRF52840_FEATHER with W5500 using Ethernet_Generic Library](#3-nrf52_simpleserver-on-adafruit-nrf52840_feather-with-w5500-using-Ethernet_Generic-library)
  * [ 4. STM32_SimpleServer on STM32F7 Nucleo-144 NUCLEO_F767ZI with W5500 using Ethernet_Generic Library](#4-stm32_simpleserver-on-stm32f7-nucleo-144-nucleo_f767zi-with-w5500-using-Ethernet_Generic-library)
  * [ 5. SAMD_SimpleServer on Adafruit SAMD51 ITSYBITSY_M4 with ESP8266_AT shield](#5-samd_simpleserver-on-adafruit-samd51-itsybitsy_m4-with-esp8266_at-shield)
  * [ 6. PWM_LEDServer_ESP32 on ESP32_DEV](#6-pwm_ledserver_esp32-on-esp32_dev)
  * [ 7. RP2040_PWM_LEDServer on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library](#7-rp2040_pwm_ledserver-on-mbed-nano_rp2040_connect-with-wifinina-using-wifinina_generic-library)
  * [ 8. RP2040_PWM_LEDServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#8-rp2040_pwm_ledserver-on-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-library)
  * [ 9. RP2040_SimpleServer on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#9-rp2040_simpleserver-on-mbed-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-library)
  * [10. PWM_LEDServer_ESP32 on ESP32S2_DEV](#10-pwm_ledserver_esp32-on-esp32s2_dev)
  * [11. PWM_LEDServer_ESP8266 on ESP8266_NODEMCU_ESP12E](#11-pwm_ledserver_esp8266-on-esp8266_nodemcu_esp12e)
  * [12. SimpleServer_WT32_ETH01 on WT32-ETH01 with ETH_PHY_LAN8720](#12-simpleserver_wt32_eth01-on-wt32-eth01-with-eth_phy_lan8720)
  * [13. Portenta_H7_SimpleServer on PORTENTA_H7_M7 using Portenta_H7 WiFi](#13-Portenta_H7_SimpleServer-on-PORTENTA_H7_M7-using-Portenta_H7-WiFi)
  * [14. Portenta_H7_SimpleServer on PORTENTA_H7_M7 using Ethernet](#14-Portenta_H7_SimpleServer-on-PORTENTA_H7_M7-using-Ethernet)
  * [15. T41_QNEthernet_SimpleServer on TEENSY 4.1](#15-T41_QNEthernet_SimpleServer-on-TEENSY-41)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)


---
---

### Important Change from v3.5.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)


### Why do we need this [UPnP_Generic library](https://github.com/khoih-prog/UPnP_Generic)

#### Features

  Many of us are **manually port-forwarding** in Internet Gateway Device (IGD, Router) in order to provide access to local Web Services from the Internet.
  
  This library provides the easier way to automatically port-forward by using the [**Simple Service Discovery Protocol (SSDP)**](https://tools.ietf.org/html/draft-cai-ssdp-v1-03), running on nRF52, SAMD21/SAMD51, STM32F/L/H/G/WB/MP1, Teensy, ESP8266/ESP32, WT32_ETH01, Portenta_H7, etc. using ESP WiFi, WiFiNINA, Ethernet W5x00, LAN8720, ESP8266/ESP32 AT-command WiFi supporting **UDP Multicast**.
  
  The SSDP provides a mechanism whereby network clients, with little or no static configuration, can discover network services. SSDP accomplishes this by providing for multicast discovery support as well as server based notification and discovery routing.
   
  The [**SSDP**](https://en.wikipedia.org/wiki/Simple_Service_Discovery_Protocol) is used for **advertisement and discovery of network services and presence information**. It accomplishes the task without assistance of server-based configuration mechanisms, such as Dynamic Host Configuration Protocol (DHCP) or Domain Name System (DNS), and without special static configuration of a network host. SSDP is the basis of the discovery protocol of **Universal Plug and Play (UPnP)** and is intended for use in residential or small office environments.
   
  This [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic) is created to automatically **update your IGDs with the requested port-forward information**, using one of the many available boards / shields. See [**Currently Supported Boards**](https://github.com/khoih-prog/UPnP_Generic#currently-supported-boards).
  
  The time between checks to update the UPnP Port Mappings is **configurable** to match your use case, and is set in the examples at 10 minutes. The LEASE_DURATION is also configurable and default to 10hrs (36000s). The Virtual Server Name can also be specified in the sketch and is shown in the IGD, e.g. `NRF52-W5X00` or `ESP8266-WIFI` as in the following picture:
  
<p align="center">
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/VirtualServers.png">
</p>

  The UPnP_Generic code is very short, can be immersed in your Projects and to be called in the loop() code.
   
  This [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic) is based on and modified from [**Ofek Pearl's TinyUPnP Library**](https://github.com/ofekp/TinyUPnP) to add support to many boards and shields besides **ESP32 and ESP8266**.

---

#### Currently Supported Boards

  - **ESP8266**
  - **ESP32**
  - **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox etc.**.
  - **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)**.
  - **Adafruit SAM21 (Itsy-Bitsy M0, Metro M0, Feather M0, Gemma M0, etc.)**.
  - **Adafruit SAM51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.
  - **Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)**
  - **STM32 (Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32F1, STM32F3, STM32F4, STM32H7, STM32L0, etc.)**.
  - **STM32F/L/H/G/WB/MP1 (Nucleo-64 L053R8,Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32Fx, STM32H7, STM32Lx, STM32Gx, STM32WB, STM32MP1, etc.) having 64K+ Flash program memory.**
  
  - RP2040-based boards, such as **Nano RP2040 Connect**, using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).

  - RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
  
  - **WT32_ETH01 boards** using ESP32-based boards and LAN8720 Ethernet
  
  - **Portenta_H7** using either `Murata WiFi` or `Vision-shield Ethernet`
  
  - **SAM DUE**
  
  - **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0)**
  
  - **AVR Mega1280, 2560, ADK.**
  
#### Currently supported WiFi shields/modules

  - **ESP8266 built-in WiFi**
  - **ESP32 built-in WiFi**
  - **WiFiNINA using WiFiNINA or WiFiNINA_Generic library**.
  - **ESP8266-AT, ESP32-AT WiFi shields using WiFiEspAT or [ESP8266_AT_WebServer](https://github.com/khoih-prog/ESP8266_AT_WebServer) library**.
  - **Portenta_H7 built-in Murata WiFi**
  
#### Currently supported Ethernet shields/modules

  - **W5x00's** using [`Ethernet_Generic`](https://github.com/khoih-prog/Ethernet_Generic) Library.
  - **Ethernet2 Library is also supported after applying the fix to add Multicast feature**. See [Libraries' Patches](https://github.com/khoih-prog/EthernetWebServer#libraries-patches)
  - ENC28J60 using EthernetENC and UIPEthernet library are not supported as UDP Multicast is not available by design.
  - LAN8742A using STM32Ethernet / STM32 LwIP libraries is not supported as UDP Multicast is not enabled by design, unless you modify the code to add support.
  - **LAN8720A in WT32-ETH01** using [`WebServer_WT32_ETH01`](https://github.com/khoih-prog/WebServer_WT32_ETH01).
  - Teensy 4.1 built-in Ethernet using [`NativeEthernet`](https://github.com/vjmuzik/NativeEthernet) library
  - Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library
  - Portenta_H7 using Ethernet from [Portenta Vision shields](https://store-usa.arduino.cc/products/arduino-portenta-vision-shield-ethernet)
  
<p align="center">
    <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/Portenta_Vision.jpg">
</p>
  
---
---
       

## Prerequisites

 1. [`Arduino IDE 1.8.16+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`ESP32 Core 2.0.2+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
 3. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/). To use ESP8266 core 2.7.1+ for LittleFS.
 4. [`Arduino AVR core 1.8.5+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) for AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 5. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 6. [`Arduino SAMD core 1.8.13+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 7. [`Adafruit SAMD core 1.7.10+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 8. [`Seeeduino SAMD core 1.8.2+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 9. [`Adafruit nRF52 v1.3.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest) 
10. [`Arduino Core for STM32 v2.2.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
11. [`ArduinoCore-mbed mbed_rp2040, mbed_nano, mbed_portenta core 3.0.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) **Portenta_H7, RP2040-based boards, such as Nano_RP2040_Connect, RASPBERRY_PI_PICO**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
12. [`Earle Philhower's arduino-pico core v1.13.1+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
13. [`Teensy core v1.56+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.

14. Depending on which Ethernet card you're using:
   - [`Ethernet_Generic library v2.0.1+`](https://github.com/khoih-prog/Ethernet_Generic) for W5100, W5200 and W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.  [![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases/latest)
15. [`WiFiNINA_Generic library v1.8.14-3+`](https://github.com/khoih-prog/WiFiNINA_Generic) to use WiFiNINA modules/shields. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic) if using WiFiNINA for boards such as Nano 33 IoT, nRF52, Teensy, etc.
16. [`WiFiWebServer library v1.7.0+`](https://github.com/khoih-prog/WiFiWebServer) to use WiFi/WiFiNINA modules/shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiWebServer.svg?)](https://www.ardu-badge.com/WiFiWebServer)
17. [`EthernetWebServer library v2.1.2+`](https://github.com/khoih-prog/EthernetWebServer) to use Ethernet modules/shields on boards other than STM32F/L/H/G/WB/MP1. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer.svg?)](https://www.ardu-badge.com/EthernetWebServer).
18. [`EthernetWebServer_STM32 library v1.4.0+`](https://github.com/khoih-prog/EthernetWebServer_STM32) to use Ethernet modules/shields on STM32F/L/H/G/WB/MP1 boards. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_STM32.svg?)](https://www.ardu-badge.com/EthernetWebServer_STM32).
19. [`ESP8266_AT_WebServer library v1.5.3+`](https://github.com/khoih-prog/ESP8266_AT_WebServer) to use ESP8266-AT/ESP32-AT WiFi modules/shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_AT_WebServer.svg?)](https://www.ardu-badge.com/ESP8266_AT_WebServer)
20. [`DDNS_Generic library v1.6.1+`](https://github.com/khoih-prog/DDNS_Generic) to use examples. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DDNS_Generic.svg?)](https://www.ardu-badge.com/DDNS_Generic)
21. [`WebServer_WT32_ETH01 library v1.4.1+`](https://github.com/khoih-prog/WebServer_WT32_ETH01) to use WT32_ETH01 (ESP32 + LAN8720). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_WT32_ETH01.svg?)](https://www.ardu-badge.com/WebServer_WT32_ETH01).
22. [`QNEthernet Library version v0.14.0+`](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet. UDP multicast has been supported. **New**


---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**UPnP_Generic**](https://github.com/khoih-prog/UPnP_Generic), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/UPnP_Generic.svg?)](https://www.ardu-badge.com/UPnP_Generic) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**UPnP_Generic**](https://github.com/khoih-prog/UPnP_Generic) page.
2. Download the latest release `UPnP_Generic-master.zip`.
3. Extract the zip file to `UPnP_Generic-master` directory 
4. Copy whole `UPnP_Generic-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**UPnP_Generic** library](https://registry.platformio.org/libraries/khoih-prog/UPnP_Generic) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/UPnP_Generic/installation). Search for **UPnP_Generic** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.13) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.13).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.13. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.13/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.9) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.9). 

Supposing the Adafruit SAMD core version is 1.7.9. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2). 

Supposing the Seeeduino SAMD core version is 1.8.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.2.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.2.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
these files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.2.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.2.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
these files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.0.0/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.0/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.0
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.0.0. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.0/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 10. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.2. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/arduino/avr/pgmspace.h`


#### 11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core
 
 To avoid compile error relating to SAMD21/SAMD51, you have to copy the file [ArduinoCore-fab-sam core pgmspace.h](Packages_Patches/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt) into `ArduinoCore-fab-sam` samd directory (~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt). 

Supposing the `ArduinoCore-fab-sam` samd core version is 1.6.18-alpha2. This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/x.yy.zz/boards.txt`


#### 12. For Seeeduino RP2040 boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino RP2040 (XIAO RP2040, Wio RP2040 Mini) boards***, you have to copy the whole [Seeeduino RP2040 Packages_Patches](Packages_Patches/Seeeduino/hardware/rp2040/2.7.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2). 

Supposing the Seeeduino SAMD core version is 2.7.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/variants/Seeed_XIAO_RP2040/pins_arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/variants/Seeed_XIAO_RP2040/pins_arduino.h`

---
---

### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.12/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

#### 8. For STM32 core F3 and F4 using UIPEthernet library

Check if you need to install the UIPEthernet patch [new STM32 core F3/F4 compatibility](https://github.com/UIPEthernet/UIPEthernet/commit/c6d6519a260166b722b9cee5dd1f0fb2682e6782) to avoid errors `#include HardwareSPI.h` on some STM32 boards (Nucleo-32 F303K8, etc.)


---
---


### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can use

```
#include <UPnP_Generic.hpp>               //https://github.com/khoih-prog/UPnP_Generic
```

in many files. But be sure to use the following `#include <NTPClient_Generic.h>` **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <UPnP_Generic.h>                //https://github.com/khoih-prog/UPnP_Generic
```

Check examples [multiFileProject_Ethernet](examples/Generic/Ethernet/multiFileProject_Ethernet) and [multiFileProject_WiFiNINA](examples/Generic/WiFiNINA/multiFileProject_WiFiNINA) for a demo how to avoid `multiple-definitions` linker error for multiple-file project

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).

---
---

### Configuration Notes

#### 1. How to use built-in WiFi in ESP8266/ESP32

It's taken care automatically.

#### 2. How to select which built-in Ethernet or shield to use

In examples' **defines.h**

1) Define UPNP_USING_ETHERNET == true and UPNP_USING_WIFI == false

```cpp
// Select UPNP_USING_WIFI for boards using built-in WiFi, such as Nano-33-IoT
#define UPNP_USING_WIFI             false
#define UPNP_USING_ETHERNET         true
```

2) To use W5x00 Ethernet, for example using Ethernet_Generic library

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      true
#define USE_ETHERNET_ESP8266      false 
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```

#### 3. How to select which built-in WiFi or shield to use

In examples' **defines.h**

1) Define UPNP_USING_WIFI == true and UPNP_USING_ETHERNET == false

```cpp
// Select UPNP_USING_WIFI for boards using built-in WiFi, such as Nano-33-IoT
#define UPNP_USING_WIFI             true
#define UPNP_USING_ETHERNET         false
```

2) To use WiFiNINA, with WiFiNINA_Generic library => Define USE_WIFI_NINA == true

```cpp
#define UPNP_USING_ETHERNET     false
#define UPNP_USING_WIFI         true

// Select one to be true: USE_WIFI_NINA, UPNP_USING_WIFI_AT or USE_WIFI_CUSTOM
#define USE_WIFI_NINA         true

// If not USE_WIFI_NINA, you can USE_WIFI_CUSTOM, then include the custom WiFi library here 
#define USE_WIFI_CUSTOM       false

...

#include <WiFiWebServer.h>
```

---

#### Important:

- The ***Ethernet_Shield_W5200, EtherCard, EtherSia  libraries are not supported***. Don't use unless you know how to modify those libraries.
- Requests to support for any future custom Ethernet library will be ignored. ***Use at your own risk***.

---

#### 4. How to select another CS/SS pin to use

The default CS/SS pin is GPIO4(D2) for ESP8266, GPIO22 for ESP32, 10 for all other boards.

If the default pin is not correct, the easiest way is to change is to use 

```cpp
// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
#define USE_THIS_SS_PIN   10
```

#### 5. How to use W5x00 with ESP8266

To avoid using the default but not-working Ethernet library of ESP8266, rename the Ethernet.h/cpp to Ethernet_ESP8266.h/cpp to avoid library conflict if you're using the Arduino Ethernet library. The Ethernet2, Ethernet3, EthernetLarge library can be used without conflict.

These pins are tested OK with ESP8266 and W5x00

```cpp
  // For ESP8266
  // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
  // Ethernet           0                 X            X            X            X        0
  // Ethernet2          X                 X            X            X            X        0
  // Ethernet3          X                 X            X            X            X        0
  // EthernetLarge      X                 X            X            X            X        0
  // Ethernet_ESP8266   0                 0            0            0            0        0
  // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
  // Must use library patch for Ethernet, EthernetLarge libraries
  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

```

#### 6. How to increase W5x00 TX/RX buffer

- For ***Ethernet3*** library only,  use as follows

```cpp
  // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
  #ifndef ETHERNET3_MAX_SOCK_NUM
    #define ETHERNET3_MAX_SOCK_NUM      4
  #endif
  
  Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
```

### 7. How to use SPI2 for ESP32 using W5x00 and Ethernet_Generic Library

- For **Ethernet_Generic** library only, to use `SPI2` for ESP32

```
#define USING_SPI2                          true
```

Pin to use for `SPI2`

```
MOSI:  13
MISO:  12
SCK:   14
SS:    5
```

### 8. How to use SPI1 for RP2040 using W5x00 and Ethernet_Generic Library

- For **Ethernet_Generic** library only, to use `SPI1` for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)

```
#define USING_SPI2                          true
```

Pin to use for `SPI1`

```
MOSI:  15
MISO:  12
SCK:   14
SS:    13
```


---

### HOWTO Usage

#### 1. Include

```
#include "UPnP.h"
#include <DDNS_Generic.h>  // optional
```

#### 2. Declare


```
UPnP* uPnP;

...

uPnP = new UPnP(30000);  // -1 means blocking, preferably, use a timeout value (ms)
```


#### 3. Setup

```
// you may repeat 'addPortMappingConfig' more than once
uPnP->addPortMappingConfig(localIP, LISTEN_PORT, RULE_PROTOCOL_TCP, LEASE_DURATION, FRIENDLY_NAME);

// finally, commit the port mappings to the IGD
int result = uPnP->commitPortMappings();

portMappingAdded = ( (result == PORT_MAP_SUCCESS) || (result == ALREADY_MAPPED) );
```

#### 4. Loop

```
// update UPnP port mapping every ms internal
// you can provide an optional method for reconnecting to the WiFi (otherwise leave as NULL)
uPnP->updatePortMappings(600000);  // 10 minutes
```

#### 5. API

This is specific for the [nRF52_PWM_LEDServer example](examples/Generic/Ethernet/nRF52/nRF52_PWM_LEDServer) to set the percentage to control the brightness of an LED:

```
http://<IP or DDNS>:<LISTEN_PORT>/?percentage=<0..100>
```

such as

```
http://192.168.2.132:5990/?percentage=20
```

or

```
http://account.duckdns.org:5990/?percentage=30
```


#### 6. Print

```
// print all the port mappings that were configured using 'addPortMappingConfig' in the setup step
uPnP->printPortMappingConfig();

// print all the current port mappings from the IGD
uPnP->printAllPortMappings();
```

---
---

### Examples:

### A. For ESP8266 and ESP32 boards

 1. [SimpleServerESP32](examples/ESP/SimpleServerESP32)
 2. [SimpleServer_ESP8266](examples/ESP/SimpleServer_ESP8266)
 3. [PWM_LEDServer_ESP32](examples/ESP/PWM_LEDServer_ESP32)
 4. [PWM_LEDServer_ESP8266](examples/ESP/PWM_LEDServer_ESP8266)

---

### B. For Ethernet shields

#### 1. nRF52

 1. [nRF52_SimpleServer](examples/Generic/Ethernet/nRF52/nRF52_SimpleServer)
 2. [nRF52_PWM_LEDServer](examples/Generic/Ethernet/nRF52/nRF52_PWM_LEDServer)
 
#### 2. RP2040

 1. [RP2040_SimpleServer](examples/Generic/Ethernet/RP2040/RP2040_SimpleServer)
 2. [RP2040_PWM_LEDServer](examples/Generic/Ethernet/RP2040/RP2040_PWM_LEDServer)

#### 3. SAMD

 1. [SAMD_SimpleServer](examples/Generic/Ethernet/SAMD/SAMD_SimpleServer)
 2. [SAMD_PWM_LEDServer](examples/Generic/Ethernet/SAMD/SAMD_PWM_LEDServer)

#### 4. STM32

 1. [STM32_SimpleServer](examples/Generic/Ethernet/STM32/STM32_SimpleServer)
 2. [STM32_PWM_LEDServer](examples/Generic/Ethernet/STM32/STM32_PWM_LEDServer)


#### 5. PORTENTA_H7

 1. [Portenta_H7_SimpleServer](examples/Generic/Ethernet/Portenta_H7/Portenta_H7_SimpleServer) **New**
 
 
#### 6. TEENSY_4.1

 1. [T41_QNEthernet_SimpleServer](examples/Generic/Ethernet/QNEthernet/T41_QNEthernet_SimpleServer) **New**

#### 7. General

 1. [multiFileProject_Ethernet](examples/Generic/Ethernet/multiFileProject_Ethernet) **New**
 
---

### C. For WiFiNINA shields

#### 1. nRF52

 1. [nRF52_SimpleServer](examples/Generic/WiFiNINA/nRF52/nRF52_SimpleServer)
 2. [nRF52_PWM_LEDServer](examples/Generic/WiFiNINA/nRF52/nRF52_PWM_LEDServer)

#### 2. RP2040

 1. [RP2040_SimpleServer](examples/Generic/WiFiNINA/RP2040/RP2040_SimpleServer)
 2. [RP2040_PWM_LEDServer](examples/Generic/WiFiNINA/RP2040/RP2040_PWM_LEDServer)

#### 3. SAMD

 1. [SAMD_SimpleServer](examples/Generic/WiFiNINA/SAMD/SAMD_SimpleServer)
 2. [SAMD_PWM_LEDServer](examples/Generic/WiFiNINA/SAMD/SAMD_PWM_LEDServer)

#### 4. STM32

 1. [STM32_SimpleServer](examples/Generic/WiFiNINA/STM32/STM32_SimpleServer)
 2. [STM32_PWM_LEDServer](examples/Generic/WiFiNINA/STM32/STM32_PWM_LEDServer)

#### 5. General

 1. [multiFileProject_WiFiNINA](examples/Generic/WiFiNINA/multiFileProject_WiFiNINA) **New**

---

### D. For ESP8266-AT/ESP32-AT shields

#### 1. nRF52

23. [nRF52_SimpleServer](examples/Generic/ESP_AT/nRF52/nRF52_SimpleServer)
24. [nRF52_PWM_LEDServer](examples/Generic/ESP_AT/nRF52/nRF52_PWM_LEDServer)

#### 2. SAMD

25. [SAMD_SimpleServer](examples/Generic/ESP_AT/SAMD/SAMD_SimpleServer)
26. [SAMD_PWM_LEDServer](examples/Generic/ESP_AT/SAMD/SAMD_PWM_LEDServer)

#### 3. STM32

27. [STM32_SimpleServer](examples/Generic/ESP_AT/STM32/STM32_SimpleServer)
28. [STM32_PWM_LEDServer](examples/Generic/ESP_AT/STM32/STM32_PWM_LEDServer)

---

### E. For WT32_ETH01 boards

29. [SimpleServer_WT32_ETH01](examples/WT32_ETH01/SimpleServer_WT32_ETH01)
30. [PWM_LEDServer_WT32_ETH01](examples/WT32_ETH01/PWM_LEDServer_WT32_ETH01)

---

### F. For WiFi shields

#### 1. PORTENTA_H7

31. [Portenta_H7_SimpleServer](examples/Generic/WiFi/Portenta_H7/Portenta_H7_SimpleServer)
32. [Portenta_H7_PWM_LEDServer](examples/Generic/WiFi/Portenta_H7/Portenta_H7_PWM_LEDServer)


---
---

### Example [nRF52_SimpleServer](examples/Generic/Ethernet/nRF52/nRF52_SimpleServer)

#### 1. File [nRF52_SimpleServer.ino](examples/Generic/Ethernet/nRF52/nRF52_SimpleServer/nRF52_SimpleServer.ino)

https://github.com/khoih-prog/UPnP_Generic/blob/702dd28f86f8b57986f948b0fad5ccc2706fb4e7/examples/Generic/Ethernet/nRF52/nRF52_SimpleServer/nRF52_SimpleServer.ino#L14-L244


#### 2. File [defines.h](examples/Generic/DuckDNS_Client/defines.h)

https://github.com/khoih-prog/UPnP_Generic/blob/702dd28f86f8b57986f948b0fad5ccc2706fb4e7/examples/Generic/Ethernet/nRF52/nRF52_SimpleServer/defines.h#L15-L199


---
---

### Debug Terminal Output Samples

#### 1. SAMD_SimpleServer on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library

Debug terminal output when running example [SAMD_SimpleServer](examples/Generic/WiFiNINA/SAMD/SAMD_SimpleServer) on SAMD21 SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library


```
Start SAMD_SimpleServer on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
UPnP_Generic v3.5.0
Connecting to HueNet1

IP address: 192.168.2.128
Add Port Forwarding, Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0
9.   SAMD-WIFI-ESPAT               192.168.2.134     5990   5990   TCP    22410
10.  NRF52-WIFI-ESPAT              192.168.2.101     7052   7052   TCP    22110
11.  STM32-WIFI-ESPAT              192.168.2.133     7032   7032   TCP    12315
12.  STM32-W5X00                   192.168.2.85      6032   6032   TCP    34005
13.  NRF52-W5X00                   192.168.2.85      5952   5952   TCP    32340
14.  STM32-LED-W5X00               192.168.2.85      6033   6033   TCP    34455
15.  SAMD-WIFININA                 192.168.2.128     5995   5995   TCP    35970

UPnP done
HTTP WiFiNINAWebServer is @ IP : 192.168.2.128, port = 5995
[DDNS] Access whatismyipaddress
Connected
[DDNS] httpCode = 200
HttpClient::responseBody => bodyLength =14
[DDNS] Current Public IP = aaa.bbb.ccc.ddd
[DDNS] response = aaa.bbb.ccc.ddd
Connected
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```

<p align="center">
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/Nano33IoT_WiFiNINA.png">
</p>

---

#### 2. nRF52_SimpleServer on Adafruit NRF52840_FEATHER with W5500 using Ethernet_Generic Library

Debug terminal output when running example [nRF52_SimpleServer](examples/Generic/Ethernet/nRF52/nRF52_SimpleServer) on Adafruit NRF52840_FEATHER with W5500 & Ethernet_Generic Library

```
Start nRF52_SimpleServer on NRF52840_FEATHER with W5x00 & Ethernet_Generic Library
UPnP_Generic v3.5.0
Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0
9.   SAMD-WIFI-ESPAT               192.168.2.101     5990   5990   TCP    35940
10.  NRF52-W5X00                   192.168.2.99      5952   5952   TCP    35985

UPnP done
HTTP EthernetWebServer is @ IP : 192.168.2.99
[DDNS] Access whatismyipaddress
[DDNS] httpCode = 200
[DDNS] Current Public IP = aaa.bbb.ccc.ddd
[DDNS] response = aaa.bbb.ccc.ddd
[DDNS] Sending HTTP_GET to duckdns
[DDNS] HTTP_GET = http://www.duckdns.org/update?domains=account.duckdns.org&token=12345678-1234-1234-1234-123456789012&ip=aaa.bbb.ccc.ddd
[DDNS] httpCode = 200
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```


<p align="center">
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/nRF52840_Ethernet2.png">
</p>

---

#### 3. nRF52_SimpleServer on Adafruit NRF52840_FEATHER with W5500 using Ethernet_Generic Library

Debug terminal output when running example [nRF52_SimpleServer](examples/Generic/Ethernet/nRF52/nRF52_SimpleServer) on Adafruit NRF52840_FEATHER with W5500 using Ethernet_Generic Library

```
Start nRF52_SimpleServer on NRF52840_FEATHER with W5x00 & Ethernet_Generic Library
UPnP_Generic v3.5.0
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5500, SSIZE =4096
**[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0
9.   SAMD-LED-W5X00                192.168.2.85      5999   5999   TCP    25355
10.  SAMD-LED-WIFININA             192.168.2.128     5996   5996   TCP    31330
11.  ESP8266-LED-WIFI              192.168.2.81      8267   8267   TCP    32265
12.  ESP32-LED-WIFI                192.168.2.82      5933   5933   TCP    33995
13.  NRF52-LED-W5X00               192.168.2.88      5953   5953   TCP    34230
14.  SAMD-W5X00                    192.168.2.84      5990   5990   TCP    35450
15.  nRF52-W5X00                   192.168.2.93      5991   5991   TCP    35970

UPnP done
HTTP EthernetWebServer is @ IP : 192.168.2.84
[DDNS] Access whatismyipaddress
[DDNS] httpCode = 200
[DDNS] Current Public IP = aaa.bbb.ccc.ddd
[DDNS] response = aaa.bbb.ccc.ddd
[DDNS] Sending HTTP_GET to duckdns
[DDNS] HTTP_GET = http://www.duckdns.org/update?domains=account.duckdns.org&token=12345678-1234-1234-1234-123456789012&ip=aaa.bbb.ccc.ddd
[DDNS] httpCode = 200
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```

<p align="center">
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/nRF52840_Ethernet.png">
</p>

and screenshot for nRF52840 NINA_B302_ublox with W5500 & Ethernet_Generic Library


<p align="center">
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/B302_Ethernet.png">
</p>

---

#### 4. STM32_SimpleServer on STM32F7 Nucleo-144 NUCLEO_F767ZI with W5500 using Ethernet_Generic Library

Debug terminal output when running example [STM32_SimpleServer](examples/Generic/Ethernet/STM32/STM32_SimpleServer) on STM32F7 Nucleo-144 NUCLEO_F767ZI with W5500 using Ethernet_Generic Library

```
Start STM32_SimpleServer on NUCLEO_F767ZI with W5x00 & Ethernet_Generic Library
UPnP_Generic v3.5.0
Add Port Forwarding, Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0
9.   SAMD-LED-WIFI-ESPAT           192.168.2.134     5991   5991   TCP    30045
10.  SAMD-WIFI-ESPAT               192.168.2.134     5990   5990   TCP    34800
11.  ESP32-LED-WIFI                192.168.2.82      5933   5933   TCP    32295
12.  STM32-W5X00                   192.168.2.85      6032   6032   TCP    35985

UPnP done
HTTP EthernetWebServer is @ IP : 192.168.2.85, port = 6032
[DDNS] Access whatismyipaddress
[DDNS] httpCode = 200
[DDNS] Current Public IP = 216.154.52.212
[DDNS] response = 216.154.52.212
[DDNS] Sending HTTP_GET to duckdns
[DDNS] HTTP_GET = http://www.duckdns.org/update?domains=account.duckdns.org&token=12345678-1234-1234-1234-123456789012&ip=216.154.52.212
[DDNS] httpCode = 200
DDNSGeneric - IP Change Detected: 216.154.52.212
[DDNS] Updated IP = 216.154.52.212

```

<p align="center">
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/F767ZI_Ethernet2.png">
</p>

---

#### 5. SAMD_SimpleServer on Adafruit SAMD51 ITSYBITSY_M4 with ESP8266_AT shield

Debug terminal output when running example [SAMD_SimpleServer](examples/Generic/ESP_AT/SAMD/SAMD_SimpleServer) on Adafruit SAMD51 ITSYBITSY_M4 with ESP8266_AT shield using [ESP8266_AT_WebServer](https://github.com/khoih-prog/ESP8266_AT_WebServer) Library

```
Start SAMD_SimpleServer on ITSYBITSY_M4 with ESP8266_AT shield
UPnP_Generic v3.5.0
WiFi shield init done

Connected to HueNet1
IP address: 192.168.2.134
Add Port Forwarding, Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0 
9.   ESP8266-WIFI                  192.168.2.81      8266   8266   TCP    18695
10.  ESP32                         192.168.2.82      5932   5932   TCP    23755
11.  SAMD-LED-WIFININA             192.168.2.128     5996   5996   TCP    29355
12.  ESP32-LED-WIFI                192.168.2.82      5933   5933   TCP    31275
13.  NRF52-LED-W5X00               192.168.2.88      5953   5953   TCP    32205
14.  SAMD-W5X00                    192.168.2.84      5990   5990   TCP    33075
15.  SAMD-LED-W5X00                192.168.2.93      5991   5991   TCP    33645
16.  SAMD-WIFI                     192.168.2.128     5995   5995   TCP    35860
17.  SAMD-WIFI-ESPAT               192.168.2.134     5990   5990   TCP    35985

UPnP done
HTTP EthernetWebServer is @ IP : 192.168.2.134, port = 5990
[DDNS] Access whatismyipaddress
[DDNS] httpCode = 200
[DDNS] Current Public IP = aaa.bbb.ccc.ddd
[DDNS] response = aaa.bbb.ccc.ddd
[DDNS] Sending HTTP_GET to duckdns
[DDNS] HTTP_GET = http://www.duckdns.org/update?domains=account.duckdns.org&token=12345678-1234-1234-1234-123456789012&ip=aaa.bbb.ccc.ddd
[DDNS] httpCode = 200
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```


<p align="center">
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/ItsyBitsy_M4_ESP8266_AT.png">
</p>

---

#### 6. PWM_LEDServer_ESP32 on ESP32_DEV

Debug terminal output when running example [PWM_LEDServer_ESP32](examples/ESP/PWM_LEDServer_ESP32) on ESP32_DEV

```
Start PWM_LEDServer_ESP32 on ESP32_DEV
UPnP_Generic v3.5.0
Connecting to HueNet1
..
IP address: 192.168.2.82
Add Port Forwarding, Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0 
9.   ESP8266-WIFI                  192.168.2.81      8266   8266   TCP    8895
10.  ESP32                         192.168.2.82      5932   5932   TCP    27705
11.  SAMD-LED-WIFININA             192.168.2.128     5996   5996   TCP    29955
12.  ESP8266-LED-WIFI              192.168.2.82      5933   5933   TCP    31575
13.  NRF52-LED-W5X00               192.168.2.88      5953   5953   TCP    32205
14.  SAMD-W5X00                    192.168.2.84      5990   5990   TCP    33075
15.  SAMD-LED-W5X00                192.168.2.93      5991   5991   TCP    33645
16.  SAMD-WIFI                     192.168.2.128     5995   5995   TCP    35460
17.  ESP32_DEV-LED-WIFI            192.168.2.81      8267   8267   TCP    35970

UPnP done
HTTP EthernetWebServer is @ IP : 192.168.2.82, port = 5932
Gateway Address: 192.168.2.1
Network Mask: 255.255.255.0
[DDNS] Current Public IP = aaa.bbb.ccc.ddd
[DDNS] Sending HTTP_GET to duckdns
[DDNS] HTTP_GET = http://www.duckdns.org/update?domains=account.duckdns.org&token=12345678-1234-1234-1234-123456789012&ip=aaa.bbb.ccc.ddd
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```

<p align="center">
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/PWM_LEDServer_ESP32.png">
</p>


---

#### 7. RP2040_PWM_LEDServer on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library

Debug terminal output when running example [RP2040_PWM_LEDServer](examples/Generic/WiFiNINA/RP2040/RP2040_PWM_LEDServer) on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library


```
Start RP2040_PWM_LEDServer on MBED NANO_RP2040_CONNECT with WiFiNINA using WiFiNINA_Generic Library
UPnP_Generic v3.5.0
Connecting to HueNet1

IP address: 192.168.2.153
Add Port Forwarding, Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0      
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0      
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0      
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0      
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0      
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0      
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0      
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0      
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0      
9.   RP2040-LED-WIFININA           192.168.2.153     6053   6053   TCP    35985  

UPnP done
HTTP WiFiWebServer is @ IP : 192.168.2.153, port = 6053
[DDNS] Access whatismyipaddress
Connected
[DDNS] httpCode = 200
HttpClient::responseBody => bodyLength =14
[DDNS] Current Public IP = aaa.bbb.ccc.ddd
[DDNS] response = aaa.bbb.ccc.ddd
Connected
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```

---


#### 8. RP2040_PWM_LEDServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

Debug terminal output when running example [RP2040_PWM_LEDServer](examples/Generic/Ethernet/RP2040/RP2040_PWM_LEDServer) on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library


```
Start RP2040_PWM_LEDServer on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
UPnP_Generic v3.5.0
Connected! IP address: 192.168.2.117
Add Port Forwarding, Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0      
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0      
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0      
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0      
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0      
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0      
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0      
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0      
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0      
9.   RP2040-LED-WIFININA           192.168.2.153     6053   6053   TCP    32580  
10.  RP2040-WIFININA               192.168.2.153     6052   6052   TCP    32850  
11.  RP2040-LED-W5X00              192.168.2.117     5953   5953   TCP    35970  

UPnP done
HTTP EthernetWebServer is @ IP : 192.168.2.117, port = 5953
Gateway Address: 192.168.2.1
Network Mask: 255.255.255.0
[DDNS] Access whatismyipaddress
Connected
[DDNS] httpCode = 200
HttpClient::responseBody => bodyLength =14
[DDNS] Current Public IP = aaa.bbb.ccc.ddd
[DDNS] response = aaa.bbb.ccc.ddd
Connected
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```

---

#### 9. RP2040_SimpleServer on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

Debug terminal output when running example [RP2040_SimpleServer](examples/Generic/Ethernet/RP2040/RP2040_SimpleServer) on MBED RASPBERRY_PI_PICO using W5x00 using Ethernet_Generic Library

```
Start RP2040_SimpleServer on MBED RASPBERRY_PI_PICO using W5x00 using Ethernet_Generic Library
UPnP_Generic v3.5.0
Connected! IP address: 192.168.2.92
Add Port Forwarding, Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0      
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0      
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0      
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0      
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0      
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0      
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0      
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0      
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0      
9.   RP2040-LED-WIFININA           192.168.2.153     6053   6053   TCP    32070  
10.  RP2040-WIFININA               192.168.2.153     6052   6052   TCP    32340  
11.  RP2040-LED-W5X00              192.168.2.117     5953   5953   TCP    35460  
12.  RP2040-W5X00                  192.168.2.92      5952   5952   TCP    35985  

UPnP done
HTTP EthernetWebServer is @ IP : 192.168.2.92, port = 5952
[DDNS] Access whatismyipaddress
Connected
[DDNS] httpCode = 200
HttpClient::responseBody => bodyLength =14
[DDNS] Current Public IP = aaa.bbb.ccc.ddd
[DDNS] response = aaa.bbb.ccc.ddd
Connected
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```

---

#### 10. PWM_LEDServer_ESP32 on ESP32S2_DEV

Debug terminal output when running example [PWM_LEDServer_ESP32](examples/ESP/PWM_LEDServer_ESP32) on ESP32S2_DEV

```
Start PWM_LEDServer_ESP32 on ESP32S2_DEV
UPnP_Generic v3.5.0
Connecting to HueNet1
.......
IP address: 192.168.2.190
Add Port Forwarding, Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0      
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0      
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0      
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0      
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0      
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0      
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0      
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0      
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0      
9.   RP2040-LED-WIFININA           192.168.2.153     6053   6053   TCP    11610  
10.  RP2040-WIFININA               192.168.2.153     6052   6052   TCP    11880  
11.  RP2040-W5X00                  192.168.2.92      5952   5952   TCP    15525  
12.  RP2040-LED-W5X00              192.168.2.119     5953   5953   TCP    16575  
13.  ESP32S2_DEV-WIFI              192.168.2.190     5932   5932   TCP    35295  
14.  ESP32S2_DEV-WIFI              192.168.2.190     5933   5933   TCP    35970  

UPnP done
HTTP WiFiWebServer is @ IP : 192.168.2.190, port = 5933
Gateway Address: 192.168.2.1
Network Mask: 255.255.255.0
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd

```

---

#### 11. PWM_LEDServer_ESP8266 on ESP8266_NODEMCU_ESP12E

Debug terminal output when running example [PWM_LEDServer_ESP32](examples/ESP/PWM_LEDServer_ESP8266) on ESP8266_NODEMCU_ESP12E

```
Start PWM_LEDServer_ESP8266 on ESP8266_NODEMCU_ESP12E
UPnP_Generic v3.5.0
Connecting to HueNet1
...........
IP address: 192.168.2.135
Add Port Forwarding, Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0      
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0      
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0      
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0      
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0      
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0      
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0      
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0      
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0      
9.   RP2040-LED-WIFININA           192.168.2.153     6053   6053   TCP    11310  
10.  RP2040-WIFININA               192.168.2.153     6052   6052   TCP    11580  
11.  RP2040-W5X00                  192.168.2.92      5952   5952   TCP    15225  
12.  RP2040-LED-W5X00              192.168.2.119     5953   5953   TCP    16275  
13.  ESP32S2_DEV-WIFI              192.168.2.190     5932   5932   TCP    34995  
14.  ESP32S2_DEV-WIFI              192.168.2.190     5933   5933   TCP    35670  
15.  ESP8266_NODEMCU_ESP12E-WIFI   192.168.2.135     8267   8267   TCP    35910  

UPnP done
HTTP WiFiWebServer is @ IP : 192.168.2.135, port = 8267
Gateway Address: 192.168.2.1
Network Mask: 255.255.255.0
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```

---

#### 12. SimpleServer_WT32_ETH01 on WT32-ETH01 with ETH_PHY_LAN8720

Debug terminal output when running example [SimpleServer_WT32_ETH01](examples/WT32_ETH01/SimpleServer_WT32_ETH01) on WT32-ETH01 with ETH_PHY_LAN8720

```
Start SimpleServer_WT32_ETH01 on WT32-ETH01 with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1
DDNS_Generic v1.6.1
UPnP_Generic v3.5.0
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232
FULL_DUPLEX, 100Mbps
IP address: 192.168.2.232
[UPnP] UDP_TX_PACKET_MAX_SIZE= 1000
[UPnP] UDP_TX_RESPONSE_MAX_SIZE= 8192
[UPnP] newUpnpRule= 0.0.0.0
Add Port Forwarding, Try # 1
[UPnP] Testing WT32_ETH01 Ethernet connection for IP : 192.168.2.232
 ==> GOOD
[UPnP] Internet connection GOOD
[UPnP] isGatewayInfoValid : 0.0.0.0 , port : 0
[UPnP] Path :  , actionPort : 0
[UPnP] actionPath :  , serviceTypeName : 
[UPnP] Gateway info not valid

[UPnP] GW IP = 192.168.2.1
[UPnP] Sending M-SEARCH to : 239.255.255.250 , Port : 1900
[UPnP] Received packet, size = 331 , IP = 192.168.2.1
[UPnP] Port = 1900
[UPnP] IGD found
[UPnP] IGD location found : http://192.168.2.1:5431/dyndev/uuid:2166898a-7de8-40ed-a1e1-b29a1d140d04
[UPnP] 192.168.2.1
[UPnP] 5431
[UPnP] /dyndev/uuid:2166898a-7de8-40ed-a1e1-b29a1d140d04
[UPnP] Connecting to IGD with host : 192.168.2.1 , port : 5431
[UPnP] Connected to IGD
[UPnP] called getIGDEventURLs
[UPnP] deviceInfo->actionPath :  , deviceInfo->path : /dyndev/uuid:2166898a-7de8-40ed-a1e1-b29a1d140d04
[UPnP] URLBase tag found : http://192.168.2.1:5431/
[UPnP] Translated to base host : 192.168.2.1  and base port : 5431
[UPnP] urn:schemas-upnp-org:service:WANPPPConnection:1 service found!
[UPnP] controlURL tag found! Setting actionPath to : /uuid:a4781538-557f-46eb-91f0-c898f3a661d5/WANPPPConnection:1
[UPnP] Port : 5431 , actionPort : 5431
[UPnP] isGatewayInfoValid : 192.168.2.1 , port : 5431
[UPnP] Path : /dyndev/uuid:2166898a-7de8-40ed-a1e1-b29a1d140d04 , actionPort : 5431
[UPnP] actionPath : /uuid:a4781538-557f-46eb-91f0-c898f3a661d5/WANPPPConnection:1 , serviceTypeName : urn:schemas-upnp-org:service:WANPPPConnection:1
[UPnP] Gateway info valid
[UPnP] Verify port mapping for rule : ESP32_DEV-WT32_ETH01
[UPnP] Apply action : GetSpecificPortMappingEntry  on port mapping : ESP32_DEV-WT32_ETH01
[UPnP] Connecting to IGD with host : 192.168.2.1 , port : 5431
[UPnP] Connected to IGD
[UPnP] Host: 192.168.2.1:5431
[UPnP] Port mapping found in IGD
[UPnP] All port mappings found in IGD, doing nothing
[UPnP] isGatewayInfoValid : 192.168.2.1 , port : 5431
[UPnP] Path : /dyndev/uuid:2166898a-7de8-40ed-a1e1-b29a1d140d04 , actionPort : 5431
[UPnP] actionPath : /uuid:a4781538-557f-46eb-91f0-c898f3a661d5/WANPPPConnection:1 , serviceTypeName : urn:schemas-upnp-org:service:WANPPPConnection:1
[UPnP] Gateway info valid
[UPnP] Connecting to IGD with host : 192.168.2.1 , port : 5431
[UPnP] Connected to IGD
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0      
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0      
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0      
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0      
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0      
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0      
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0      
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0      
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0      
9.   ESP8266_NODEMCU_ESP12E-WIFI   192.168.2.36      8266   8266   TCP    33690  
76.  ESP32_DEV-WT32_ETH01          192.168.2.232     5931   5931   TCP    35070  

UPnP done
HTTP WiFiWebServer is @ IP : 192.168.2.232, port = 5931
Gateway Address: 192.168.2.1
Network Mask: 255.255.255.0
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```

<p align="center">
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/WT32_ETH01.png">
</p>

---

#### 13. Portenta_H7_SimpleServer on PORTENTA_H7_M7 using Portenta_H7 WiFi

Debug terminal output when running example [Portenta_H7_SimpleServer](examples/Generic/WiFi/Portenta_H7/Portenta_H7_SimpleServer) on PORTENTA_H7_M7 using Portenta_H7 WiFi

```
Start Portenta_H7_SimpleServer on PORTENTA_H7_M7 using Portenta_H7 WiFi
UPnP_Generic v3.5.0
Connecting to HueNet1

IP address: 192.168.2.130
Add Port Forwarding, Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0      
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0      
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0      
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0      
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0      
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0      
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0      
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0      
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0      
9.   Portenta_H7-WIFI              192.168.2.130     6032   6032   TCP    35970  

UPnP done
HTTP WiFiWebServer is @ IP : 192.168.2.130, port = 6032
[DDNS] Access whatismyipaddress
Connected
[DDNS] httpCode = 200
HttpClient::responseBody => bodyLength =15
[DDNS] Current Public IP = aaa.bbb.ccc.ddd
[DDNS] response = aaa.bbb.ccc.ddd
Connected
DDNSGeneric - IP Change Detected: aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```

---

#### 14. Portenta_H7_SimpleServer on PORTENTA_H7_M7 using Ethernet

Debug terminal output when running example [Portenta_H7_SimpleServer](examples/Generic/Ethernet/Portenta_H7/Portenta_H7_SimpleServer) on PORTENTA_H7_M7 using Ethernet using Portenta_Ethernet Library

```
Start Portenta_H7_SimpleServer on PORTENTA_H7_M7 using Ethernet using Portenta_Ethernet Library
UPnP_Generic v3.5.0
Add Port Forwarding, Try # 1
[UPnP] IGD current port mappings:
0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0      
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0      
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0      
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0      
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0      
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0      
9.   Portenta_H7-LED-WIFI          192.168.2.130     6033   6033   TCP    35040  
10.  Portenta_H7-ETH               192.168.2.132     6032   6032   TCP    35970  

UPnP done
HTTP EthernetWebServer is @ IP : 192.168.2.132, port = 6032
[DDNS] Access whatismyipaddress
Connected
[DDNS] httpCode = 200
HttpClient::responseBody => bodyLength =15
[DDNS] Current Public IP = aaa.bbb.ccc.ddd
[DDNS] response = aaa.bbb.ccc.ddd
Connected
DDNSGeneric - IP Change Detected: oldIP = , newIP = aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```

---

#### 15. T41_QNEthernet_SimpleServer on TEENSY 4.1

Debug terminal output when running example [T41_QNEthernet_SimpleServer](examples/Generic/Ethernet/QNEthernet/T41_QNEthernet_SimpleServer) on Teensy 4.1 using built-in Ethernet with QNEthernet Library


```
Start T41_QNEthernet_SimpleServer on TEENSY 4.1
UPnP_Generic v3.5.0
IP Address = 192.168.2.123
[UPnP] UDP_TX_PACKET_MAX_SIZE= 1000
[UPnP] UDP_TX_RESPONSE_MAX_SIZE= 8192
[UPnP] newUpnpRule= 0.0.0.0
Add Port Forwarding, Try # 1
[UPnP] Internet connection GOOD
[UPnP] isGatewayInfoValid : 0.0.0.0 , port : 0
[UPnP] Path :  , actionPort : 0
[UPnP] actionPath :  , serviceTypeName : 
[UPnP] Gateway info not valid

[UPnP] GW IP = 192.168.2.1
[UPnP] Sending M-SEARCH to : 239.255.255.250 , Port : 1900
[UPnP] Received packet, size = 331 , IP = 192.168.2.1
[UPnP] Port = 1900
[UPnP] IGD found
[UPnP] IGD location found : http://192.168.2.1:5431/dyndev/uuid:23a5ccd0-54ea-4ff8-9607-26c3b838e44c
[UPnP] 192.168.2.1
[UPnP] 5431
[UPnP] /dyndev/uuid:23a5ccd0-54ea-4ff8-9607-26c3b838e44c
[UPnP] Connecting to IGD with host : 192.168.2.1 , port : 5431
[UPnP] Connected to IGD
[UPnP] called getIGDEventURLs
[UPnP] deviceInfo->actionPath :  , deviceInfo->path : /dyndev/uuid:23a5ccd0-54ea-4ff8-9607-26c3b838e44c
[UPnP] URLBase tag found : http://192.168.2.1:5431/
[UPnP] Translated to base host : 192.168.2.1  and base port : 5431
[UPnP] urn:schemas-upnp-org:service:WANPPPConnection:1 service found!
[UPnP] controlURL tag found! Setting actionPath to : /uuid:3e3d865a-8e93-453c-998d-0049f6ff26f5/WANPPPConnection:1
[UPnP] Port : 5431 , actionPort : 5431
[UPnP] isGatewayInfoValid : 192.168.2.1 , port : 5431
[UPnP] Path : /dyndev/uuid:23a5ccd0-54ea-4ff8-9607-26c3b838e44c , actionPort : 5431
[UPnP] actionPath : /uuid:3e3d865a-8e93-453c-998d-0049f6ff26f5/WANPPPConnection:1 , serviceTypeName : urn:schemas-upnp-org:service:WANPPPConnection:1
[UPnP] Gateway info valid
[UPnP] Verify port mapping for rule : T41-QNEth
[UPnP] Apply action : GetSpecificPortMappingEntry  on port mapping : T41-QNEth
[UPnP] Connecting to IGD with host : 192.168.2.1 , port : 5431
[UPnP] Connected to IGD
[UPnP] Host: 192.168.2.1:5431
[UPnP] Port mapping found in IGD
[UPnP] All port mappings found in IGD, doing nothing
[UPnP] isGatewayInfoValid : 192.168.2.1 , port : 5431
[UPnP] Path : /dyndev/uuid:23a5ccd0-54ea-4ff8-9607-26c3b838e44c , actionPort : 5431
[UPnP] actionPath : /uuid:3e3d865a-8e93-453c-998d-0049f6ff26f5/WANPPPConnection:1 , serviceTypeName : urn:schemas-upnp-org:service:WANPPPConnection:1
[UPnP] Gateway info valid
[UPnP] Connecting to IGD with host : 192.168.2.1 , port : 5431
[UPnP] Connected to IGD
[UPnP] IGD current port mappings:

0.   Blynk Server                  192.168.2.110     9443   9443   TCP    0      
1.   Blynk WebServer               192.168.2.110     80     80     TCP    0      
2.   Blynk Hardware Server         192.168.2.110     8080   8080   TCP    0      
3.   Blynk Server                  192.168.2.110     9443   1443   TCP    0      
4.   Blynk Secondary Server        192.168.2.112     9443   2443   TCP    0      
5.   Blynk Sec. Hardware Server    192.168.2.112     8080   1080   TCP    0      
6.   Blynk Server SSL              192.168.2.110     9443   443    TCP    0      
7.   MariaDB / MySQL               192.168.2.112     5698   5698   TCP    0      
8.   MariaDB / MySQL               192.168.2.112     3306   3306   TCP    0      
9.   T41-QNEth                     192.168.2.123     6032   6032   TCP    35355

UPnP done
HTTP EthernetWebServer is @ IP : 192.168.2.123, port = 6032
[DDNS] Access ifconfig.me
Connected
[DDNS] httpCode = 200
HttpClient::responseBody => bodyLength =-1
[DDNS] Current Public IP = aaa.bbb.ccc.ddd
[DDNS] response = aaa.bbb.ccc.ddd
Connected
DDNSGeneric - IP Change Detected: oldIP = , newIP = aaa.bbb.ccc.ddd
[DDNS] Updated IP = aaa.bbb.ccc.ddd
```


---
---

### Debug

Debug is enabled by default on Serial. To disable, add at the beginning of sketch

```cpp
/* Comment this out to disable prints and save space */
// Debug Level from 0 to 4
#define _DDNS_GENERIC_LOGLEVEL_     1
#define _UPNP_LOGLEVEL_             3
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, dependent libraries or this library version.

Sometimes, the library will only work if you update the core to the newer or older version because some function compatibility.

---
---

  
### Issues

Submit issues to: [UPnP_Generic issues](https://github.com/khoih-prog/UPnP_Generic/issues)
  
---
---

### TO DO

1. Bug Searching and Killing
2. Support more non-compatible Ethernet Libraries such as Ethernet_Shield_W5200, EtherCard, EtherSia


### DONE

 1. Add support to Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)
 2. Add support to Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.).
 3. Add support to Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.).
 4. Add support to Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.
 5. Add support to Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)
 6. Add support to STM32F/L/H/G/WB/MP1 (Nucleo-144, Nucleo-64, Nucleo-32, Discovery, STM32Fx, STM32H7, STM32Lx, STM32Gx, STM32WB, STM32MP1, etc.) having 64K+ Flash program memory.
 7. Add support to Ethernet W5x00, using either [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`Ethernet2`](https://github.com/khoih-prog/Ethernet2), [`Ethernet3`](https://github.com/sstaub/Ethernet3) or [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge) library
 8. Add support to WiFiNINA using WiFiNINA or WiFiNINA_Generic library.
 9. Add support to ESP8266-AT, ESP32-AT WiFi shields using [ESP8266_AT_WebServer](https://github.com/khoih-prog/ESP8266_AT_WebServer) or WiFiEspAT library.
10. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico core**](https://github.com/earlephilhower/arduino-pico).
11. Add support to RP2040-based boards, such as **NANO_RP2040_CONNECT, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).
12. Add Version String and Table of Contents
13. Add support to **WT32_ETH01 boards** using ESP32-based boards and LAN8720 Ethernet
14. Add support to **Portenta_H7**, using either `Murata WiFi` or `Vision-shield Ethernet`
15. Use new [**Ethernet_Generic** library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
16. Support **SPI2 for ESP32**
17. Add support to SPI1 for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
18. Add example [multiFileProject_Ethernet](examples/Generic/Ethernet/multiFileProject_Ethernet) and [multiFileProject_WiFiNINA](examples/Generic/WiFiNINA/multiFileProject_WiFiNINA) to demo how to avoid `multiple-definitions` linker error for multiple-file project
19. Add support to Teensy 4.1 built-in Ethernet using [`NativeEthernet`](https://github.com/vjmuzik/NativeEthernet) library
20. Add support to Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library


---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Based on and modified from the [**Ofek Pearl's TinyUPnP Library**](https://github.com/ofekp/TinyUPnP) to add support to many boards and shields besides **ESP32 and ESP8266**
2. Thanks to good work of [Miguel Wisintainer](https://github.com/tcpipchip) for working with, developing, debugging and testing.

<table>
  <tr>
    <td align="center"><a href="https://github.com/ofekp"><img src="https://github.com/ofekp.png" width="100px;" alt="ofekp"/><br /><sub><b>⭐️ Ofek Pearl</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>⭐️ Miguel Wisintainer</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [GPLv3.0](https://github.com/khoih-prog/UPnP_Generic/blob/master/LICENSE)

---

## Copyright

Copyright 2020- Khoi Hoang




