This example contains Atmel Studio 7 project for ATMega32U4 (but could be modified to any other chip in AVR serie with clasic GPIO controlled by DDR, PORT and PIN registers). This demo shows up how to read device flash. It shows correct seqeunce of entering programming mode, reading flash to buffer and exiting programming mode. Default pinout is following. You can change it in `Nuvoton8051PlatformSpecific.h` file. Attached device must run at 5V. If you have Nuvoton powered by 3V source you need to disconnect it first. Otherwise you burn your Nuvoton! If you need to power Nuvoton using 3V you must power AVR also 3V or use level converter on RST, ICPCLK and ICPDAT lines and disconnect connection between powering pins. Common GND must remain. Note that some pasive level converters cant works with signal as fast as 1MHz which is used when programming device.

```
Nuvoton's    GND <------> GND on AVR
Nuvoton's    VCC <------> 5V  on AVR
Nuvoton's    RST <------> PD1 on AVR
Nuvoton's ICPCLK <------> PD4 on AVR
Nuvoton's ICPDAT <------> PD0 on AVR
```

Example is implemented in `main.c` file and contains small TX only UART implementation that expects that your AVR is running at 16 Mhz. Baudrate is set to 9600. If you have your own UART library or need different baudrate or frequence you need to remove and replace all UART logic in `main.c` file with your own.

Program then reads device flash per 128B blocks because of limited ammount of RAM on AVR devices and prints it over UART. Example output is following.

```
Flash content:
02 08 4a 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
...
...
...
```

If you see only FF check your wiring and check that your Nuvoton is powered.
