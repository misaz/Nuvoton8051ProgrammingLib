This example contains Atmel Studio 7 project for ATMega32U4 (but could be modified to any other chip in AVR serie with clasic GPIO controlled by DDR, PORT and PIN registers). This demo shows up how to write device flash. It shows correct seqeunce of entering programming mode, reading flash to buffer and exiting programming mode. Default pinout is following. You can change it in `Nuvoton8051PlatformSpecific.h` file. Attached device must run at 5V. If you have Nuvoton powered by 3V source you need to disconnect it first. Otherwise you burn your Nuvoton! If you need to power Nuvoton using 3V you must power AVR also 3V or use level converter on RST, ICPCLK and ICPDAT lines and disconnect connection between powering pins. Common GND must remain. Note that some pasive level converters cant works with signal as fast as 1MHz which is used when programming device.


```
Nuvoton's    GND <------> GND on AVR
Nuvoton's    VCC <------> 5V  on AVR
Nuvoton's    RST <------> PD1 on AVR
Nuvoton's ICPCLK <------> PD4 on AVR
Nuvoton's ICPDAT <------> PD0 on AVR
```

Flashed program must be in specified header format. If you have hex file (file `blink.hex` in example) with your firmware that you want flash. You need to convert it using following commands. That commands convert HEX file to BIN file and then using xdd generates header file containing program bytes. `blink.h` is included in program sources.

```
objcopy -I ihex blink.hex -O binary blink.bin
xxd -i blink.bin > blink.h
```

Example is implemented in `main.c` file and includes `blink.h` file specified above. When running program erases connected MCU and flash it using contents of blink_bin array defined in `blink.h` file.