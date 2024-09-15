# USB IR Remote Receiver based on CH32V003
The **IR2USB** is a compact device designed to receive signals from an infrared (IR) remote control and translate them into keyboard or mouse inputs. It resembles a USB stick with an integrated IR receiver. When plugged into a computer, the IR2USB registers as a USB Human Interface Device (HID), meaning it requires no additional drivers to function. The device is powered by the cost-effective 32-bit RISC-V microcontroller CH32V003, which processes the IR signals and converts them into standard USB HID commands, allowing seamless control of a computer using an IR remote.

![IR2USB_pic1.jpg](https://raw.githubusercontent.com/wagiminator/CH32V003-USB-IR-Receiver/main/documentation/IR2USB_pic1.jpg)

If you don’t have a suitable infrared remote control at hand, just build one yourself: [CH32V003 IR Remote Control](https://github.com/wagiminator/CH32V003-IR-Remote).

# Hardware
## Schematic
![IR2USB_wiring.png](https://raw.githubusercontent.com/wagiminator/CH32V003-USB-IR-Receiver/main/documentation/IR2USB_wiring.png)

## The CH32V003 Family of 32-bit RISC-V Microcontrollers
The CH32V003 series is a collection of industrial-grade general-purpose microcontrollers that utilize the QingKe RISC-V2A core design supporting the RV32EC instruction set. These microcontrollers are equipped with various features such as a 48MHz system main frequency, 16KB flash, 2KB SRAM, 2.7V - 5.5V supply voltage support, a single-wire serial debug interface, low power consumption, and an ultra-small package. Additionally, the CH32V003 series includes a built-in set of components including a DMA controller, a 10-bit ADC, op-amp comparators, multiple timers, and standard communication interfaces such as USART, I2C, and SPI.

## Building Instructions
1. Take the Gerber files (the *zip* file inside the *hardware* folder) and upload them to a PCB (printed circuit board) manufacturer of your choice (e.g., [JLCPCB](https://jlcpcb.com/)). They will use these files to create the circuit board for your device and send it to you.
2. Once you have the PCB, you can start soldering the components onto it. Use the BOM (bill of materials) and schematic as a guide to make sure everything is connected correctly. You can find the corresponding files in the *hardware* folder.
3. Upload the firmware by following the instructions in the next section (see below).

![IR2USB_pic3.jpg](https://raw.githubusercontent.com/wagiminator/CH32V003-USB-IR-Receiver/main/documentation/IR2USB_pic3.jpg)

# Software
## Software USB
Since the CH32V003 lacks a hardware USB peripheral, USB functionality is handled in software. Charles Lohr's excellent implementation, [RV003USB](https://github.com/cnlohr/rv003usb), is used for this. It emulates a USB low-speed device using pin-change interrupts and bit-banging, with assembly code for the low-level protocol and some C code for higher-level functionality.

## Firmware Versions
### IR Multimedia Control
This firmware for the **IR2USB** device is designed to enable the control of multimedia applications on a PC via an infrared (IR) remote. It interprets IR signals from a remote control and converts them into standard multimedia keyboard inputs. Key features of the firmware include:

- **Volume Control**: The IR signals for volume up and down buttons on the remote are mapped to corresponding multimedia keys for increasing or decreasing the system volume.
- **Media Playback Control**: The firmware supports functions such as play, pause, stop, next track, and previous track, allowing users to control audio and video players seamlessly.
- **Mute Functionality**: A dedicated IR signal is mapped to the mute/unmute command to quickly toggle sound.
- **Plug-and-Play**: The firmware runs on the **CH32V003** microcontroller and ensures the device appears as a USB Human Interface Device (HID) when connected to the PC, requiring no drivers. 

### IR Mouse Control
This firmware for the **IR2USB** device allows full control of the mouse pointer and mouse buttons via an infrared (IR) remote control. It translates IR signals into standard mouse inputs, providing a seamless way to navigate a PC interface. Key features of the firmware include:

- **Mouse Pointer Movement**: IR signals are mapped to control the movement of the mouse cursor. Directional buttons on the remote (up, down, left, right) are translated into corresponding cursor movements, with adjustable speed for smooth navigation.
- **Mouse Buttons**: The firmware supports the translation of IR signals into mouse button clicks. Commonly, the "OK" or "Enter" button on the remote can be mapped to the left mouse button, and another button (such as "Back" or "Menu") can be mapped to the right mouse button.
- **Scrolling**: The firmware allows for vertical and horizontal scrolling. Additional buttons on the remote can be mapped to simulate mouse wheel scrolling, making it easy to navigate web pages or documents.
- **Plug-and-Play**: The device appears as a standard USB Human Interface Device (HID) and requires no additional drivers, making setup effortless.

### IR Presenter
This firmware for the **IR2USB** device is tailored for controlling presentations, such as PowerPoint slideshows, via an infrared (IR) remote control. It translates IR signals into keyboard inputs commonly used for managing presentations, providing an efficient way to navigate slides. Key features include:

- **Slide Navigation**: The IR remote's directional buttons (e.g., "Left" and "Right" or "Up" and "Down") are mapped to keyboard inputs for navigating between slides. Typically, these are mapped to the left and right arrow keys or the Page Up and Page Down keys to move forward and backward in the presentation.
- **Start/End Presentation**: Dedicated buttons on the remote can be mapped to the "F5" key to start a presentation and "Esc" to exit the slideshow. This allows the presenter to begin and end the presentation without touching the computer.
- **Blank Screen**: A button can be mapped to the "B" key to toggle a blank screen during the presentation, which is useful for pausing and resuming focus during talks.
- **Volume Control**: For presentations with embedded audio or video, the remote can include volume up/down control by mapping specific buttons to media keys for adjusting system volume.
- **Plug-and-Play**: The device appears as a standard USB Human Interface Device (HID) and requires no additional drivers, making setup effortless.

## Customizing the Firmware
The configuration of the device address and button commands from the infrared remote control to specific actions can be customized in the *config.h* file. This allows the **IR2USB** device to be adapted to work with your chosen remote control for the desired application. Currently, the firmware only supports the **NEC protocol**, which is widely used by most remote controls, particularly the inexpensive ones often found in China-based stores.

If you don't have a suitable remote control, you can also build one yourself. Links to DIY projects for creating your own remote are provided below.

## Programming and Debugging Device
To program the CH32V003 microcontroller, you will need a special programming device which utilizes the proprietary single-wire serial debug interface (SDI). The [WCH-LinkE](http://www.wch-ic.com/products/WCH-Link.html) (pay attention to the "E" in the name) is a suitable device for this purpose and can be purchased commercially for around $4. This debugging tool is not only compatible with the CH32V003 but also with other WCH RISC-V and ARM-based microcontrollers.

![CH32V003_wch-linke.jpg](https://raw.githubusercontent.com/wagiminator/Development-Boards/main/CH32V003F4P6_DevBoard/documentation/CH32V003_wch-linke.jpg)

To use the WCH-LinkE on Linux, you need to grant access permissions beforehand by executing the following commands:
```
echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="1a86", ATTR{idProduct}=="8010", MODE="666"' | sudo tee /etc/udev/rules.d/99-WCH-LinkE.rules
echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="1a86", ATTR{idProduct}=="8012", MODE="666"' | sudo tee -a /etc/udev/rules.d/99-WCH-LinkE.rules
sudo udevadm control --reload-rules
```

On Windows, if you need to you can install the WinUSB driver over the WCH interface 1 using the [Zadig](https://zadig.akeo.ie/) tool.

To upload the firmware, you need to ensure that the IR2USB Adapter is disconnected from USB. Then, you should make the following connections to the WCH-LinkE:

```
WCH-LinkE       IR2USB
+-------+      +------+
|  SWDIO| <--> |DIO   |
|    GND| ---> |GND   |
|    3V3| ---> |VCC   |
+-------+      +------+
```

If the blue LED on the WCH-LinkE remains illuminated once it is connected to the USB port, it means that the device is currently in ARM mode and must be switched to RISC-V mode initially. There are a few ways to accomplish this:
- You can utilize the Python command-line tool [rvprog](https://pypi.org/project/rvprog/) (with *-v* option).
- Alternatively, you can select "WCH-LinkRV" in the software provided by WCH, such as MounRiver Studio or WCH-LinkUtility.
- Another option is to hold down the ModeS button on the device while plugging it into the USB port.

More information can be found in the [WCH-Link User Manual](http://www.wch-ic.com/downloads/WCH-LinkUserManual_PDF.html).

## Compiling and Uploading Firmware using the Makefile
### Linux
Install the toolchain (GCC compiler, Python3, and rvprog):
```
sudo apt install build-essential libnewlib-dev gcc-riscv64-unknown-elf
sudo apt install python3 python3-pip
pip install rvprog
```

Disconnect the IR2USB Adapter from the USB port. Connect the IR2USB Adapter via the 3-pin PROG header to the WCH-LinkE programming device. Open a terminal and navigate to the folder with the *makefile*. Run the following command to compile and upload:
```
make flash
```

### Other Operating Systems
Follow the instructions on [CNLohr's ch32v003fun page](https://github.com/cnlohr/ch32v003fun/wiki/Installation) to set up the toolchain on your respective operating system (for Windows, use WSL). Also, install [Python3](https://www.pythontutorial.net/getting-started/install-python/) and [rvprog](https://pypi.org/project/rvprog/). Compile and upload with "make flash". Note that I only have Debian-based Linux and have not tested it on other operating systems.

## Uploading pre-compiled Firmware Binary
WCH offers the free but closed-source software [WCH-LinkUtility](https://www.wch.cn/downloads/WCH-LinkUtility_ZIP.html) to upload the precompiled hex-file with Windows. Select the "WCH-LinkRV" mode in the software, open the *<firmware>.hex* file in the *bin* folder and upload it to the microcontroller.

Alternatively, there is an open-source tool called [minichlink](https://github.com/cnlohr/ch32v003fun/tree/master/minichlink) developed by Charles Lohr (CNLohr). It can be used with Windows, Linux and Mac.

If you have installed [Python3](https://www.pythontutorial.net/getting-started/install-python/) on your system, you can also use the platform-independent open-source command-line tool [rvprog](https://pypi.org/project/rvprog/) for uploading:
```
rvprog -f bin/<firmware>.bin
```

# References, Links and Notes
- [EasyEDA Design Files](https://oshwlab.com/wagiminator)
- [CNLohr: rv003usb](https://github.com/cnlohr/rv003usb)
- [MCU Templates](https://github.com/wagiminator/MCU-Templates)
- [MCU Flash Tools](https://github.com/wagiminator/MCU-Flash-Tools)
- [CH32V003 Datasheets](http://www.wch-ic.com/products/CH32V003.html)
- [CH32V003 5-Button IR Remote Control](https://github.com/wagiminator/CH32V003-IR-Remote)
- [ATtiny13A 5-Button IR Remote Control](https://github.com/wagiminator/ATtiny13-TinyRemote)
- [ATtiny13A 12-Button IR Remote Control](https://github.com/wagiminator/ATtiny13-TinyRemoteXL)

![IR2USB_pic2.jpg](https://raw.githubusercontent.com/wagiminator/CH32V003-USB-IR-Receiver/main/documentation/IR2USB_pic2.jpg)

# License
![license.png](https://i.creativecommons.org/l/by-sa/3.0/88x31.png)

This work is licensed under Creative Commons Attribution-ShareAlike 3.0 Unported License. 
(http://creativecommons.org/licenses/by-sa/3.0/)
