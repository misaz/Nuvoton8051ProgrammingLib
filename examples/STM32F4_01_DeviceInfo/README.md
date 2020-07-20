This example contains Attolic True Studio project for STM32F429ZI (but could be modified to any other chip in STM32F4xx serie) that read device info from Nuvoton MCU connected to it using GPIO. It shows correct seqeunce of entering programming mode, reading informations and exiting programming mode. Default pinout is following. You can change it in `Nuvoton8051PlatformSpecific.h` file. Attached device must running at 3V. If you have any 5V source connected to Nuvoton (like USB power on some development boards) you need to disconnect it first. Otherwise you burn your raspberry pi! If you need to power Nuvoton using 5V you must use level converter on RST, ICPCLK and ICPDAT lines and disconnect connection between powering pins. Common GND must remain. Note that some pasive level converters cant works with signal as fast as 1MHz which is used when programming device.

```
Nuvoton's    GND <------> GND  on STM32F4
Nuvoton's    VCC <------> 3V   on STM32F4
Nuvoton's    RST <------> PG2  on STM32F4
Nuvoton's ICPCLK <------> PD14 on STM32F4
Nuvoton's ICPDAT <------> PD12 on STM32F4
```

Example is implemented in `main.c` file and expect that you have debugger attached to it. If you do not have (or do not use) debugger you need to write some UART printing (or similar) logic.

In Variables window and you will see CID, PID and DID of your connected Nuvoton. If you see only 0xFF  (255) and 0xFFFF (65535) as values check your wiring and check that your Nuvoton is powered.

![Output shown in debugger](/img/STM32F4_01_DeviceInfo_DebuggerResult.png)