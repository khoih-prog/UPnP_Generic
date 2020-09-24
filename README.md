## UPnP_Generic Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/UPnP_Generic.svg?)](https://www.ardu-badge.com/UPnP_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/UPnP_Generic.svg)](https://github.com/khoih-prog/UPnP_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/UPnP_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/UPnP_Generic.svg)](http://github.com/khoih-prog/UPnP_Generic/issues)

---
---

### Why do we need this [UPnP_Generic library](https://github.com/khoih-prog/UPnP_Generic)

  Many of us are **manually port-forwarding** in Internet Gateway Device (IGD, Router) in order to provide access to local Web Services from the Internet.
  
  This library provides the easier way to automatically port-forward by using the [**Simple Service Discovery Protocol (SSDP)**](https://tools.ietf.org/html/draft-cai-ssdp-v1-03), running on nRF52, SAMD21/SAMD51, STM32F/L/H/G/WB/MP1, Teensy, ESP8266/ESP32, using ESP WiFi, WiFiNINA, Ethernet W5x00, ESP8266/ESP32 AT-command WiFi supporting **UDP Multicast**.
  
  The SSDP provides a mechanism whereby network clients, with little or no static configuration, can discover network services. SSDP accomplishes this by providing for multicast discovery support as well as server based notification and discovery routing.
   
  The [**SSDP**](https://en.wikipedia.org/wiki/Simple_Service_Discovery_Protocol) is used for **advertisement and discovery of network services and presence information**. It accomplishes the task without assistance of server-based configuration mechanisms, such as Dynamic Host Configuration Protocol (DHCP) or Domain Name System (DNS), and without special static configuration of a network host. SSDP is the basis of the discovery protocol of **Universal Plug and Play (UPnP)** and is intended for use in residential or small office environments.
   
  This [UPnP_Generic library](https://github.com/khoih-prog/UPnP_Generic) is created to automatically **update your IGDs with the requested port-forward information**, using one of the many available boards / shields. See [Currently Supported Boards](https://github.com/khoih-prog/UPnP_Generic#currently-supported-boards).
  
  The time between checks to update the UPnP Port Mappings is **configurable** to match your use case, and is set in the examples at 10 minutes. The LEASE_DURATION is also configurable and default to 10hrs (36000s). The Virtual Server Name can also be specified in the sketch and is shown in the IGD, e.g. `NRF52-W5X00` or `ESP8266-WIFI` as in the following picture:
  
<p align="center">
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/VirtualServers.png">
</p>

  The UPnP_Generic code is very short, can be immersed in your Projects and to be called in the loop() code.
   
  This [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic) is based on and modified from [**Ofek Pearl's TinyUPnP Library**](https://github.com/ofekp/TinyUPnP) to add support to many boards and shields besides **ESP32 and ESP8266**.

---

### Releases v3.1.4

1. Initial coding for Generic boards using many different WiFi/Ethernet modules/shields.
2. Add more examples

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
  
#### Currently Supported WiFi Modules/Shields

  - **ESP8266 built-in WiFi**
  - **ESP32 built-in WiFi**
  - **WiFiNINA using WiFiNINA or WiFiNINA_Generic library**.
  - **ESP8266-AT, ESP32-AT WiFi shields using WiFiEspAT or [ESP8266_AT_WebServer](https://github.com/khoih-prog/ESP8266_AT_WebServer) library**.
  
#### Currently Supported Ethernet Modules/Shields

  - **W5x00's using Ethernet, EthernetLarge or Ethernet3 Library.**
  - **Ethernet2 Library is also supported after applying the fix to add Multicast feature**. See [Libraries' Patches](https://github.com/khoih-prog/EthernetWebServer#libraries-patches)
  - ENC28J60 using EthernetENC or UIPEthernet library is not supported as UDP Multicast is not available by design.
  - LAN8742A using STM32Ethernet / STM32 LwIP libraries is not supported as UDP Multicast is not enabled by design, unless you modify the code to add support.
  
---
---

## Prerequisite

 1. [`Arduino IDE 1.8.12+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino AVR core 1.8.3+`](https://github.com/arduino/ArduinoCore-avr) for Arduino AVR boards. Use Arduino Board Manager to install.
 3. [`ESP32 core 1.0.4+`](https://github.com/espressif/arduino-esp32/releases) for ESP32 boards
 4. [`ESP8266 core 2.7.3+` for Arduino](https://github.com/esp8266/Arduino#installing-with-boards-manager) for ESP8266 boards. To use ESP8266 core 2.7.1+ for LittleFS.
 5. [`Teensy core 1.53+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards. **Not ready in v1.0.0.**
 6. [`Arduino SAM DUE core 1.6.12+`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 7. [`Arduino SAMD core 1.8.8+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards (Nano 33 IoT, etc.).
 8. [`Adafruit SAMD core 1.6.0+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Itsy-Bitsy M4, etc.)
 9. [`Adafruit nRF52 v0.20.5+`](https://www.adafruit.com/) for nRF52 boards such as AdaFruit Feather nRF52840 Express, NINA_B302_ublox, etc.
10. [`Arduino Core for STM32 v1.9.0+`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards. To install go to Arduino IDE, select Boards Manager, search for **`STM32`**
11. [`Seeeduino SAMD core 1.7.8+`](https://www.seeedstudio.com/) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.)
12. Depending on which Ethernet card you're using:
   - [`Ethernet library v2.0.0+`](https://www.arduino.cc/en/Reference/Ethernet) for W5100, W5200 and W5500.
   - [`Ethernet2 library v1.0.4+`](https://github.com/khoih-prog/Ethernet2) for W5500 (Deprecated, use Arduino Ethernet library). After applying Multicast support.
   - [`Ethernet3 library v1.5.3+`](https://github.com/sstaub/Ethernet3) for W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.
   - [`EthernetLarge library v2.0.0+`](https://github.com/OPEnSLab-OSU/EthernetLarge) for W5100, W5200 and W5500.
13. [`WiFiNINA_Generic library v1.7.1+`](https://github.com/khoih-prog/WiFiNINA_Generic) to use WiFiNINA modules/shields. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic) if using WiFiNINA for boards such as Nano 33 IoT, nRF52, Teensy, etc.
14. [`WiFiWebServer library v1.0.6+`](https://github.com/khoih-prog/WiFiWebServer) to use WiFi/WiFiNINA modules/shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiWebServer.svg?)](https://www.ardu-badge.com/WiFiWebServer)
15. [`EthernetWebServer library v1.0.12+`](https://github.com/khoih-prog/EthernetWebServer) to use Ethernet modules/shields on boards other than STM32F/L/H/G/WB/MP1. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer.svg?)](https://www.ardu-badge.com/EthernetWebServer).
16. [`EthernetWebServer_STM32 library v1.0.5+`](https://github.com/khoih-prog/EthernetWebServer_STM32) to use Ethernet modules/shields on STM32F/L/H/G/WB/MP1 boards. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_STM32.svg?)](https://www.ardu-badge.com/EthernetWebServer_STM32).
17. [`ESP8266_AT_WebServer library v1.1.0+`](https://github.com/khoih-prog/ESP8266_AT_WebServer) to use ESP8266-AT/ESP32-AT WiFi modules/shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_AT_WebServer.svg?)](https://www.ardu-badge.com/ESP8266_AT_WebServer)

---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `UPnP_Generic`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/UPnP_Generic.svg?)](https://www.ardu-badge.com/UPnP_Generic) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [UPnP_Generic](https://github.com/khoih-prog/UPnP_Generic) page.
2. Download the latest release `UPnP_Generic-master.zip`.
3. Extract the zip file to `UPnP_Generic-master` directory 
4. Copy whole `UPnP_Generic-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:
1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install **UPnP_Generic** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/). Search for UPnP_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---

### Packages' Patches

 1. ***To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards***, you have to copy the whole [nRF52 0.20.5](Packages_Patches/adafruit/hardware/nrf52/0.20.5) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5). 

Supposing the Adafruit nRF52 version is 0.20.5. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B112_ublox/variant.cpp`
- ***`~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/cores/nRF5/Udp.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- ***`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`***

 2. ***To be able to compile and run on Teensy boards***, you have to copy the file [Teensy boards.txt](Packages_Patches/hardware/teensy/avr/boards.txt) into Teensy hardware directory (./arduino-1.8.12/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.12. This file must be copied into the directory:

- `./arduino-1.8.12/hardware/teensy/avr/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`

 3. ***To be able to compile and run on SAM DUE boards***, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

 4. ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.8](Packages_Patches/arduino/hardware/samd/1.8.8) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.8).
 
Supposing the Arduino SAMD version is 1.8.8. These files must be copied into the directory:
- `~/.arduino15/packages/arduino/hardware/samd/1.8.8/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.8/cores/arduino/Arduino.h`***

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

 5. ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.0) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.0). 

Supposing the Adafruit SAMD core version is 1.6.0. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

 6. ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.7.8) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.7.8). 

Supposing the Seeeduino SAMD core version is 1.7.8. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.7.8/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

7. ***To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards***, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`

---

### Libraries' Patches

1. If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

2. To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

3. To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)

4. To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for this [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

6. ***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

7. To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.12/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

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

2) To use W5x00 Ethernet, for example using EthernetLarge library

```cpp
  #define USE_UIP_ETHERNET        false
  #define USE_CUSTOM_ETHERNET     false

  // Only one if the following to be true
  #define USE_ETHERNET            false
  #define USE_ETHERNET2           false
  #define USE_ETHERNET3           false
  #define USE_ETHERNET_LARGE      true
  #define USE_ETHERNET_ESP8266    false
  #define USE_ETHERNET_ENC        false
```

3) To use W5x00 Ethernet, for example using Ethernet3 library

```cpp
  #define USE_UIP_ETHERNET        false
  #define USE_CUSTOM_ETHERNET     false

  // Only one if the following to be true
  #define USE_ETHERNET            false
  #define USE_ETHERNET2           false
  #define USE_ETHERNET3           true
  #define USE_ETHERNET_LARGE      false
  #define USE_ETHERNET_ESP8266    false
  #define USE_ETHERNET_ENC        false
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

If the default pin is not corect, the easiest way is to change is to use 

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

### B. For Ethernet shields

#### 1. nRF52

 5. [nRF52_SimpleServer](examples/Generic/Ethernet/nRF52/nRF52_SimpleServer)
 6. [nRF52_PWM_LEDServer](examples/Generic/Ethernet/nRF52/nRF52_PWM_LEDServer)

#### 2. SAMD

 7. [SAMD_SimpleServer](examples/Generic/Ethernet/SAMD/SAMD_SimpleServer)
 8. [SAMD_PWM_LEDServer](examples/Generic/Ethernet/SAMD/SAMD_PWM_LEDServer)

#### 3. STM32

 9. [STM32_SimpleServer](examples/Generic/Ethernet/STM32/STM32_SimpleServer)
10. [STM32_PWM_LEDServer](examples/Generic/Ethernet/STM32/STM32_PWM_LEDServer)


### C. For WiFiNINA shields

#### 1. nRF52

11. [nRF52_SimpleServer](examples/Generic/WiFiNINA/nRF52/nRF52_SimpleServer)
12. [nRF52_PWM_LEDServer](examples/Generic/WiFiNINA/nRF52/nRF52_PWM_LEDServer)

#### 2. SAMD

13. [SAMD_SimpleServer](examples/Generic/WiFiNINA/SAMD/SAMD_SimpleServer)
14. [SAMD_PWM_LEDServer](examples/Generic/WiFiNINA/SAMD/SAMD_PWM_LEDServer)

#### 3. STM32

15. [STM32_SimpleServer](examples/Generic/WiFiNINA/STM32/STM32_SimpleServer)
16. [STM32_PWM_LEDServer](examples/Generic/WiFiNINA/STM32/STM32_PWM_LEDServer)

### D. For ESP8266-AT/ESP32-AT shields

#### 1. nRF52

17. [nRF52_SimpleServer](examples/Generic/ESP_AT/nRF52/nRF52_SimpleServer)
18. [nRF52_PWM_LEDServer](examples/Generic/ESP_AT/nRF52/nRF52_PWM_LEDServer)

#### 2. SAMD

19. [SAMD_SimpleServer](examples/Generic/ESP_AT/SAMD/SAMD_SimpleServer)
20. [SAMD_PWM_LEDServer](examples/Generic/ESP_AT/SAMD/SAMD_PWM_LEDServer)

#### 3. STM32

21. [STM32_SimpleServer](examples/Generic/ESP_AT/STM32/STM32_SimpleServer)
22. [STM32_PWM_LEDServer](examples/Generic/ESP_AT/STM32/STM32_PWM_LEDServer)

---
---

### Example [nRF52_SimpleServer](examples/Generic/Ethernet/nRF52/nRF52_SimpleServer)

#### 1. File [nRF52_SimpleServer.ino](examples/Generic/Ethernet/nRF52/nRF52_SimpleServer/nRF52_SimpleServer.ino)


```cpp
#include "defines.h"

#define UPNP_USING_ETHERNET     true

#include <UPnP_Generic.h>

#define LISTEN_PORT         5952
#define LEASE_DURATION      36000  // seconds
#define FRIENDLY_NAME       "NRF52-W5X00"  // this name will appear in your router port forwarding section

UPnP* uPnP;

EthernetWebServer server(LISTEN_PORT);

const int led = 13;

void onUpdateCallback(const char* oldIP, const char* newIP)
{
  Serial.print("DDNSGeneric - IP Change Detected: ");
  Serial.println(newIP);
}

void handleRoot()
{
#define BUFFER_SIZE     400
  
  digitalWrite(led, 1);
  char temp[BUFFER_SIZE];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  int day = hr / 24;

  snprintf(temp, BUFFER_SIZE - 1,
           "<html>\
<head>\
<meta http-equiv='refresh' content='5'/>\
<title>%s</title>\
<style>\
body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
</style>\
</head>\
<body>\
<h1>Hello from %s</h1>\
<h3>running UPnP_Generic & DDNS_Generic</h3>\
<h3>on %s</h3>\
<p>Uptime: %d d %02d:%02d:%02d</p>\
</body>\
</html>", BOARD_NAME, BOARD_NAME, SHIELD_TYPE, day, hr, min % 60, sec % 60);

  server.send(200, "text/html", temp);
  digitalWrite(led, 0);
}

void handleNotFound() 
{
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  
  for (uint8_t i = 0; i < server.args(); i++) 
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) 
{
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart nRF52_SimpleServer on " + String(BOARD_NAME));
  Serial.println(" with " + String(SHIELD_TYPE));
  
  ET_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);

  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
  ET_LOGWARN(F("========================="));

  #if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
    // For other boards, to change if necessary
    #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2  || USE_ETHERNET_ENC )
      // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
      Ethernet.init (USE_THIS_SS_PIN);
    
    #elif USE_ETHERNET3
      // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
      #ifndef ETHERNET3_MAX_SOCK_NUM
        #define ETHERNET3_MAX_SOCK_NUM      4
      #endif
    
      Ethernet.setCsPin (USE_THIS_SS_PIN);
      Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
  
    #elif USE_CUSTOM_ETHERNET
      // You have to add initialization for your Custom Ethernet here
      // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
      //Ethernet.init(USE_THIS_SS_PIN);
      
    #endif  //( ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2  || USE_ETHERNET_ENC )
  #endif
  
  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  IPAddress localIP = Ethernet.localIP();

  ////////////////
  
  DDNSGeneric.service("duckdns");    // Enter your DDNS Service Name - "duckdns" / "noip"

  /*
    For DDNS Providers where you get a token:
    DDNSGeneric.client("domain", "token");

    For DDNS Providers where you get username and password: ( Leave the password field empty "" if not required )
    DDNSGeneric.client("domain", "username", "password");
  */
  DDNSGeneric.client("account.duckdns.org", "12345678-1234-1234-1234-123456789012");

  DDNSGeneric.onUpdate(onUpdateCallback);

  ////////////////

  uPnP = new UPnP(60000);  // -1 means blocking, preferably, use a timeout value (ms)

  if (uPnP)
  {
    uPnP->addPortMappingConfig(localIP, LISTEN_PORT, RULE_PROTOCOL_TCP, LEASE_DURATION, FRIENDLY_NAME);

    bool portMappingAdded = false;

#define RETRY_TIMES     4
    int retries = 0;

    while (!portMappingAdded && (retries < RETRY_TIMES))
    {
      Serial.println("Add Port Forwarding, Try # " + String(++retries));

      int result = uPnP->commitPortMappings();

      portMappingAdded = ( (result == PORT_MAP_SUCCESS) || (result == ALREADY_MAPPED) );

      //Serial.println("commitPortMappings result =" + String(result));

      if (!portMappingAdded)
      {
        // for debugging, you can see this in your router too under forwarding or UPnP
        //uPnP->printAllPortMappings();
        //Serial.println(F("This was printed because adding the required port mapping failed"));
        if (retries < RETRY_TIMES)
          delay(10000);  // 10 seconds before trying again
      }
    }

    uPnP->printAllPortMappings();

    Serial.println("\nUPnP done");
  }
  
  server.on("/", handleRoot);

  server.on("/inline", []()
  {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();

  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
  Serial.print(localIP); 
  Serial.print(", port = ");
  Serial.println(LISTEN_PORT);
}

void loop(void) 
{
  DDNSGeneric.update(300000);

  uPnP->updatePortMappings(600000);  // 10 minutes

  server.handleClient();
}
```

#### 2. File [defines.h](examples/Generic/DuckDNS_Client/defines.h)


```cpp
#ifndef defines_h
#define defines_h

// Debug Level from 0 to 4
#define _DDNS_GENERIC_LOGLEVEL_     1
#define _UPNP_LOGLEVEL_             2

// Select DDNS_USING_WIFI for boards using built-in WiFi, such as Nano-33-IoT
#define DDNS_USING_WIFI             false
#define DDNS_USING_ETHERNET         true

/////////////////////////////////
  
#if !( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )

  #error This code is intended to run on the nRF52 platform! Please check your Tools->Board setting.
#endif

/////////////////////////////////

#if defined(ETHERNET_USE_NRF528XX)
  #undef ETHERNET_USE_NRF528XX
#endif

#define ETHERNET_USE_NRF528XX          true
#warning Use NRF52 architecture with Ethernet   

// Default pin 10 to SS/CS
#define USE_THIS_SS_PIN       10

/////////////////////////////////
  
#if defined(NRF52840_FEATHER)
  #define BOARD_TYPE      "NRF52840_FEATHER_EXPRESS"
#elif defined(NRF52832_FEATHER)
  #define BOARD_TYPE      "NRF52832_FEATHER"
#elif defined(NRF52840_FEATHER_SENSE)
  #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
#elif defined(NRF52840_ITSYBITSY)
  #define BOARD_TYPE      "NRF52840_ITSYBITSY_EXPRESS"
#elif defined(NRF52840_CIRCUITPLAY)
  #define BOARD_TYPE      "NRF52840_CIRCUIT_PLAYGROUND"
#elif defined(NRF52840_CLUE)
  #define BOARD_TYPE      "NRF52840_CLUE"
#elif defined(NRF52840_METRO)
  #define BOARD_TYPE      "NRF52840_METRO_EXPRESS"
#elif defined(NRF52840_PCA10056)
  #define BOARD_TYPE      "NORDIC_NRF52840DK"
#elif defined(NINA_B302_ublox)
  #define BOARD_TYPE      "NINA_B302_ublox"
#elif defined(NINA_B112_ublox)
  #define BOARD_TYPE      "NINA_B112_ublox"
#elif defined(PARTICLE_XENON)
  #define BOARD_TYPE      "PARTICLE_XENON"
#elif defined(MDBT50Q_RX)
  #define BOARD_TYPE      "RAYTAC_MDBT50Q_RX"
#elif defined(ARDUINO_NRF52_ADAFRUIT)
  #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
#else
  #define BOARD_TYPE      "nRF52 Unknown"
#endif


///////////////////////////////////////////
// Select Ethernet Library for the Shield
///////////////////////////////////////////

#define USE_UIP_ETHERNET        false
#define USE_CUSTOM_ETHERNET     false

// Only one if the following to be true
#define USE_ETHERNET            false
#define USE_ETHERNET2           true //true
#define USE_ETHERNET3           false //true
#define USE_ETHERNET_LARGE      false
#define USE_ETHERNET_ESP8266    false //true
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
```

---
---

### Debug Termimal Output Samples

#### 1. Debug terminal output when running example [SAMD_SimpleServer](examples/Generic/WiFiNINA/SAMD/SAMD_SimpleServer) on SAMD21 SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library

```
Start SAMD_SimpleServer on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
Connecting to WPA SSID: HueNet1
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
9.   SAMD-WIFI-ESPAT               192.168.2.101     5990   5990   TCP    35475
10.  SAMD-WIFI                     192.168.2.128     5999   5999   TCP    35985

UPnP done
HTTP EthernetWebServer is @ IP : 192.168.2.128
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
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/Nano33IoT_WiFiNINA.png">
</p>


and screenshot for nRF52840 NINA_B302_ublox with W102 WiFiNINA using WiFiNINA_Generic Library


<p align="center">
  <img src="https://github.com/khoih-prog/UPnP_Generic/blob/master/pics/B302_WiFiNINA.png">
</p>

---

#### 2. Debug terminal output when running example [nRF52_SimpleServer](examples/Generic/Ethernet/nRF52/nRF52_SimpleServer) on Adafruit NRF52840_FEATHER with with W5500 & Ethernet2 Library

```
Start nRF52_SimpleServer on NRF52840_FEATHER with W5x00 & Ethernet2 Library
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

#### 3. Debug terminal output when running example [nRF52_SimpleServer](examples/Generic/Ethernet/nRF52/nRF52_SimpleServer) on Adafruit NRF52840_FEATHER with W5500 using Ethernet Library

```
Start nRF52_SimpleServer on NRF52840_FEATHER with W5x00 & Ethernet Library
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

---

#### 4. Debug terminal output when running example [STM32_SimpleServer](examples/Generic/Ethernet/STM32/STM32_SimpleServer) on STM32F7 Nucleo-144 NUCLEO_F767ZI with W5500 using Ethernet3 Library

```
Start STM32_SimpleServer on NUCLEO_F767ZI with W5x00 & Ethernet2 Library
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

#### 5. Debug terminal output when running example [SAMD_SimpleServer](examples/Generic/ESP_AT/SAMD/SAMD_SimpleServer) on Adafruit SAMD51 ITSYBITSY_M4 with ESP8266_AT shield using [ESP8266_AT_WebServer](https://github.com/khoih-prog/ESP8266_AT_WebServer) Library

```
Start SAMD_SimpleServer on ITSYBITSY_M4 with ESP8266_AT shield
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

#### 6. Debug terminal output when running example [PWM_LEDServer_ESP32](examples/ESP/PWM_LEDServer_ESP32) on ESP32_DEV

```
Start PWM_LEDServer_ESP32 on ESP32_DEV
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
17.  ESP32-LED-WIFI                192.168.2.81      8267   8267   TCP    35970

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
---

## Releases

### Releases v3.1.4

1. Initial coding for Generic boards using many different WiFi/Ethernet modules/shields.
2. Add more examples

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
  -
  
#### Currently Supported WiFi Modules/Shields

  - **ESP8266 built-in WiFi**
  - **ESP32 built-in WiFi**
  - **WiFiNINA using WiFiNINA or WiFiNINA_Generic library**.
  - **ESP8266-AT, ESP32-AT WiFi shields using WiFiEspAT or [ESP8266_AT_WebServer](https://github.com/khoih-prog/ESP8266_AT_WebServer) library**.
  
#### Currently Supported Ethernet Modules/Shields

  - **W5x00's using Ethernet, EthernetLarge or Ethernet3 Library.**
  - **Ethernet2 Library is also supported after applying the fix to add Multicast feature**. See [Libraries' Patches](https://github.com/khoih-prog/EthernetWebServer#libraries-patches)
  - ENC28J60 using EthernetENC or UIPEthernet library is not supported as UDP Multicast is not available by design.
  - LAN872A using STM32Ethernet / STM32 LwIP libraries is not supported as UDP Multicast is not enabled by design, unless you modify the code to add support.
  
---

### TO DO

1. Bug Searching and Killing
2. Support more types of boards using WiFi/Ethernet shields (Teensy, AVR Nano/UNO/Mega, etc.)
3. Support more non-compatible Ethernet Libraries such as Ethernet_Shield_W5200, EtherCard, EtherSia


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

- The library is licensed under [MIT](https://github.com/khoih-prog/EthernetWebServer/blob/master/LICENSE)

---

## Copyright

Copyright 2020- Khoi Hoang




