# Fork for PlatformIO nRF52840 with Arduino and Zigbee Support

This project is part of multiple git repositories for an Android framework with Zigbee support. The aim is to include the support in the fantastic work of Adafruit and all other contrubutors.

- [platform-nordicnrf52](https://github.com/csowada/platform-nordicnrf52)
- [Adafruit_nRF52_Arduino](https://github.com/csowada/Adafruit_nRF52_Arduino)
- [Adafruit_TinyUSB_ArduinoCore](https://github.com/csowada/Adafruit_TinyUSB_ArduinoCore)

### Known Limitations

- Not working with Arduino IDE
- No clue if TinyUSB is working
- Bootloader/MBR is untested
- Some Serial stuff is disabled, see ``Uart.c`` file.
- SOFTDEVICE as in Adafruits version is not working
- Only nRF52840-DK is supported/tested yet

### Modifications to ``platform-nordicnrf52``

- Add clone of Adafruit ``adafruit.py`` builder with NO-SD support
- Add build scripts for additional features like Zigbee
- Add new ``nrf52840_dk_zb`` board
- Add ``xxx`` Zigbee bulb example

### Modifications to ``Adafruit_nRF52_Arduino``

- Backport ``nrfx`` from 2.1.0 to 1.8.0 from Zigbee SDK 1.4.1
- Change RTC1 to RTC0 for FreeRTOS
- Fix some functions for NON-SOFTDEVICE
- Remove from lines for Serial
- Add required Zigbee stuff and libraries

### Modifications to ``Adafruit_TinyUSB_ArduinoCore``

- Backport some function calls due to ``nrfx`` backport

## Usage

Add the forked platform etc. to your ``platformio.ini`` file. This works without any downloads, PlatformIO will do that for you.

```ini
platform = https://github.com/csowada/platform-nordicnrf52.git
platform_packages = framework-arduinonordicnrf52-zb-sdk @ https://github.com/csowada/Adafruit_nRF52_Arduino.git

board = nrf52840_dk_zb
framework = arduino

custom_enable_features = 
  ; Add Zigbee support to the core build
  ZIGBEE

build_flags =
  ; Add SDK relevant flags here
  -DZIGBEE_CHANNEL=11
  -DZB_TRACE_LEVEL=0
  -DZB_TRACE_MASK=0
  -DUSE_APP_CONFIG
  -DAPP_TIMER_V2
  -DAPP_TIMER_V2_RTC1_ENABLED
  -DCONFIG_GPIO_AS_PINRESET
  -DENABLE_FEM
  -DFLOAT_ABI_HARD
```

To run this framework, add an ``config`` folder to your project to place the ``sdk_config.h`` file there.

## Examples

See the ``arduino-zigbee-bulb`` in [Adafruit_nRF52_Arduino](https://github.com/csowada/Adafruit_nRF52_Arduino).



***

# Arduino Core for Adafruit Bluefruit nRF52 Boards

This repository contains the Arduino BSP for Adafruit Bluefruit nRF52 series:

- [Adafruit CLUE nRF52840](https://www.adafruit.com/product/4500)
- [Adafruit Circuit Playground Bluefruit](https://www.adafruit.com/product/4333)
- [Adafruit Feather nRF52832](https://www.adafruit.com/product/3406)
- [Adafruit Feather nRF52840 Express](https://www.adafruit.com/product/4062)
- [Adafruit Feather nRF52840 Sense](https://www.adafruit.com/product/4516)
- [Adafruit ItsyBitsy nRF52840 Express](https://www.adafruit.com/product/4481)
- Adafruit Metro nRF52840 Express

Following boards are also included but are not officially supported:

- [Nordic nRF52840DK PCA10056](https://www.nordicsemi.com/Software-and-Tools/Development-Kits/nRF52840-DK)
- [Particle Xenon](https://store.particle.io/products/xenon)

## BSP Installation

There are two methods that you can use to install this BSP. We highly recommend the first option unless you wish to participate in active development of this codebase via Github.

### Recommended: Adafruit nRF52 BSP via the Arduino Board Manager

 1. [Download and install the Arduino IDE](https://www.arduino.cc/en/Main/Software) (At least v1.6.12)
 2. Start the Arduino IDE
 3. Go into Preferences
 4. Add https://www.adafruit.com/package_adafruit_index.json as an 'Additional Board Manager URL'
 5. Restart the Arduino IDE
 6. Open the Boards Manager from the Tools -> Board menu and install 'Adafruit nRF52 by Adafruit'
 7. Once the BSP is installed, select 'Adafruit Bluefruit nRF52 Feather' from the Tools -> Board menu, which will update your system config to use the right compiler and settings for the nRF52.

### Optional (Core Development): Adafruit nRF52 BSP via git

 1. Install BSP via Board Manager as above to install compiler & tools.
 2. Delete the core folder `nrf52` installed by Board Manager in Adruino15, depending on your OS. It could be
  * macOS  : `~/Library/Arduino15/packages/adafruit/hardware/nrf52`
  * Linux  : `~/.arduino15/packages/adafruit/hardware/nrf52`
  * Windows: `%APPDATA%\Local\Arduino15\packages\adafruit\hardware\nrf52`
 3. `cd <SKETCHBOOK>`, where `<SKETCHBOOK>` is your Arduino Sketch folder:
  * macOS  : `~/Documents/Arduino`
  * Linux  : `~/Arduino`
  * Windows: `~/Documents/Arduino`
 4. Create a folder named `hardware/Adafruit`, if it does not exist, and change directories to it
 5. Clone this repo & its submodules: `git clone --recurse-submodules https://github.com/adafruit/Adafruit_nRF52_Arduino.git`
 6. Restart the Arduino IDE
 7. Once the BSP is installed, select 'Adafruit Bluefruit nRF52 Feather' from the Tools -> Board menu, which will update your system config to use the right compiler and settings for the nRF52.

### Adafruit's nrfutil tools

[adafruit-nrfutil](https://github.com/adafruit/Adafruit_nRF52_nrfutil) (derived from Nordic pc-nrfutil) is needed to upload sketch via serial port.

- For Windows and macOS, pre-built executable binaries are included in the BSP at `tools/adafruit-nrfutil/`. It should work out of the box.
- Linux user need to run follow command to install it from PyPi

```
$ pip3 install adafruit-nrfutil --user
```

### Drivers

- [SiLabs CP2104 driver](http://www.silabs.com/products/mcu/pages/usbtouartbridgevcpdrivers.aspx) is required for USB to Serial when using with Feather nRF52832

## Bootloader Support

### Upgrade existing Bootloader

Bluefruit's Bootloader is self-upgradable, you could upgrade to the latest Bootloader + Softdevice using the serial port within Arduino IDE.

- Select `Tools > Board > Adafruit Bluefruit Feather52`
- Select `Tools > Programmer > Bootloader DFU for Bluefruit nRF52`
- Select `Tools > Burn Bootloader`
- **WAIT** until the process complete ~30 seconds

**Note: close the Serial Monitor before you click "Burn Bootloader". Afterwards, you shouldn't close the Arduino IDE, unplug the Feather, launch Serial Monitor etc ... to abort the process. There is a high chance it will brick your device! Do this with care and caution.**

### Burning new Bootloader

To burn the bootloader from within the Arduino IDE, you will need the following tools installed
on your system and available in the system path:

- Segger [JLink Software and Documentation Pack](https://www.segger.com/downloads/jlink)
- Nordic [nRF5x Command Line Tools](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Command-Line-Tools)

Check to make sure you can run `nrfjprog` from your terminal/command prompt

**macOS Note** At present, you will need to create a symlink in `/usr/local/bin` to the
`nrfjprog` tool wherever you have added it. You can run the following command, for example:

```
$ ln -s $HOME/prog/nordic/nrfjprog/nrfjprog /usr/local/bin/nrfjprog
```

Once the tools above have been installed and added to your system path, from the Arduino IDE:

- Select `Tools > Board > Adafruit Bluefruit Feather52`
- Select `Tools > Programmer > J-Link for Feather52`
- Select `Tools > Burn Bootloader` with the board and J-Link connected

If you wish to modify bootloader to your own need, check out its repo here [Adafruit_nRF52_Bootloader](https://github.com/adafruit/Adafruit_nRF52_Bootloader)

#### Manually Burning the Bootloader via nrfjprog

The bootloader hex file can be found at `bin/bootloader` run the command as follows:

```
$ nrfjprog -e -f nrf52
$ nrfjprog --program feather_nrf52832_bootloader.hex -f nrf52
$ nrfjprog --reset -f nrf52
```

## Credits

This core is based on [Arduino-nRF5](https://github.com/sandeepmistry/arduino-nRF5) by Sandeep Mistry,
which in turn is based on the [Arduino SAMD Core](https://github.com/arduino/ArduinoCore-samd).

The following libraries are used:

- adafruit-nrfutil is based on Nordic Semiconductor ASA's [pc-nrfutil](https://github.com/NordicSemiconductor/pc-nrfutil)
- [freeRTOS](https://www.freertos.org/) as operating system
- [tinyusb](https://github.com/hathach/tinyusb) as usb stack
- [nrfx](https://github.com/NordicSemiconductor/nrfx) for peripherals driver
- [littlefs](https://github.com/ARMmbed/littlefs) for internal file system
