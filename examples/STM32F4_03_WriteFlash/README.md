This example contains Attolic True Studio project for STM32F429ZI (but could be modified to any other chip in STM32F4xx serie) that write flash of device. It shows correct seqeunce of entering programming mode, writing flash to buffer and exiting programming mode. Default pinout is following. You can change it in `Nuvoton8051PlatformSpecific.h` file. Attached device must running at 3V. If you have any 5V source connected to Nuvoton (like USB power on some development boards) you need to disconnect it first. Otherwise you burn your raspberry pi! If you need to power Nuvoton using 5V you must use level converter on RST, ICPCLK and ICPDAT lines and disconnect connection between powering pins. Common GND must remain. Note that some pasive level converters cant works with signal as fast as 1MHz which is used when programming device.

```
Nuvoton's    GND <------> GND  on STM32F4
Nuvoton's    VCC <------> 3V   on STM32F4
Nuvoton's    RST <------> PG2  on STM32F4
Nuvoton's ICPCLK <------> PD14 on STM32F4
Nuvoton's ICPDAT <------> PD12 on STM32F4
```

Flashed program must be in specified header format. If you have hex (file `blink.hex` in example) file of your firmware that you want flash convert it using following commands. That commands convert HEX file to BIN file and then using xdd generates header file containing program bytes. `blink.h` is included in program sources.

```
objcopy -I ihex blink.hex -O binary blink.bin
xxd -i blink.bin > blink.h
```

Example is implemented in `main.c` file and includes `blink.h` file specified above. When running program erases connected MCU and flash it using contents of blink_bin array defined in `blink.h` file.