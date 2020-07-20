This example contains application for Raspberry Pi that read first 8KiB of content of flash from Nuvoton MCU connected to Raspberry Pi using GPIO. It shows correct seqeunce of entering programming mode, reading flash to buffer and exiting programming mode. Default pinout is following. You can change it in `Nuvoton8051PlatformSpecific.h` file. Attached device must running at 3V. If you have any 5V source connected to Nuvoton (like USB power on some development boards) you need to disconnect it first. Otherwise you burn your raspberry pi! If you need to power Nuvoton using 5V you must use level converter on RST, ICPCLK and ICPDAT lines and disconnect connection between powering pins. Common GND must remain. Note that some pasive level converters cant works with signal as fast as 1MHz which is used when programming device.

```
Nuvoton's    GND <------> GND   (pin #9) on Raspberry Pi
Nuvoton's    VCC <------> 3V    (pin #1) on Raspberry Pi
Nuvoton's    RST <------> GPIO2 (pin #3) on Raspberry Pi
Nuvoton's ICPCLK <------> GPIO3 (pin #5) on Raspberry Pi
Nuvoton's ICPDAT <------> GPIO4 (pin #7) on Raspberry Pi
```

Example is implemented in `main.c` file and program saves content of flash into `firmware_read.bin` file. Compile is done on Raspberry Pi using GCC. Clang should also work.

```
gcc main.c Nuvoton8051.c Nuvoton8051PlatformSpecific.c -Wall -pedantic -o demo
```

There are also Makefile containing that command. Soo you can run simly make.

```
make
```

Then you can run demo program using following command

```
sudo ./demo
```

Program have no output (in case of success) but you can see that file `firmware_read.bin` was created.