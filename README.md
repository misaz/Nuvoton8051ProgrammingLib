# Nuvoton 8051 Serie MCU Programming library
This project contains library that can be used to flash and configure cheep Novuton's 8051 serie microcontrollers by any other microcontroller like AVR (Arduino), STM32, Raspberry Pi or any other. Library is multiplatform and independent on any other library. When used It consists of 4 files. Files `Nuvoton8051.c` and `Nuvoton8051.h` contains library itself. There are declared and defined library functions needded to manipulate connected microcontroller. In your app include only `Nuvoton8051.h` file. `Nuvoton8051.c` and `Nuvoton8051.h` files depends on platform specific implementation of GPIO access and time delay. Platform specific implementation is provided in `Nuvoton8051PlatformSpecific.c` and `Nuvoton8051PlatformSpecific.h` files. If you want to use this library you need to implement it.

Library was tested agains Nuvoton N76E003 chip but probably works with mostly all other 8051 based Nuvoton's microcontrollers. It does not work with ARM based MCUs at all.

There are provided also reference implementation for following platforms. If you want to use it, delete default Nuvoton8051PlatformSpecific.c and Nuvoton8051PlatformSpecific.h files and rename files for your platform to correct names. Then delete any other PlatformSpecific files for other unnescessary platforms (for. example if you are using AVR, delete `Nuvoton8051PlatformSpecific_STM32F4.c` and so on). Delete both h and c files.

If you want to use it on platform that is not implemented. Just implement functions in Nuvoton8051PlatformSpecific.c file and delete other unnescessary PlatformSpecific files like `Nuvoton8051PlatformSpecific_AVR.c` and `Nuvoton8051PlatformSpecific_STM32F4.c`.

## AVR
Provided platform specific files directly access GPIO registers (PORTx, PINx, DDRx) and for delay uses `_delay_us` function. Default pinout is following:

```
Nuvoton's    RST <------> PD1 on AVR
Nuvoton's ICPCLK <------> PD4 on AVR
Nuvoton's ICPDAT <------> PD0 on AVR
```

If you want to use it do following:
1) Copy library to your project.
2) Delete all unnescessary files for other platforms like `Nuvoton8051PlatformSpecific_STM32F4.c` and `Nuvoton8051PlatformSpecific_STM32F4.h`. Only files `Nuvoton8051.c`, `Nuvoton8051.h`, `Nuvoton8051PlatformSpecific_AVR.c` and `Nuvoton8051PlatformSpecific_AVR.h` must be present.
3) Rename `Nuvoton8051PlatformSpecific_AVR.c` -> `Nuvoton8051PlatformSpecific.c` (remove `_AVR` suffix from name)
4) Rename `Nuvoton8051PlatformSpecific_AVR.h` -> `Nuvoton8051PlatformSpecific.h` (remove `_AVR` suffix from name)
5) Include library into your app using `#include "Nuvoton8051.h"`
6) Write and test your application code. See examples bellow.

## STM32F4 
Provided platform spcific files uses StdPeriph driver. If you use another driver consider implementing platform spcific functions in the same way as if you are running on unsupported platform. While it looks strange on the first look It is easy. Use `Nuvoton8051PlatformSpecific_STM32F4.c` as reference.

Note that you must diconnect any 5V power suply when connected to STM32 and power Nuvoton only by 3.3V max. Otherwise you burn your STM32.

Default pinout is following:

```
Nuvoton's    RST <------> PG2  on STM32F4
Nuvoton's ICPCLK <------> PD14 on STM32F4
Nuvoton's ICPDAT <------> PD12 on STM32F4
```

If you want to use it do following:
1) Copy library to your project.
2) Delete all unnescessary files for other platforms like `Nuvoton8051PlatformSpecific_AVR.c` and `Nuvoton8051PlatformSpecific_AVR.h`. Only files `Nuvoton8051.c`, `Nuvoton8051.h`, `Nuvoton8051PlatformSpecific_STM32F4.c` and `Nuvoton8051PlatformSpecific_STM32F4.h` must be present.
3) Rename `Nuvoton8051PlatformSpecific_STM32F4.c` -> `Nuvoton8051PlatformSpecific.c` (remove `_STM32F4` suffix from name)
4) Rename `Nuvoton8051PlatformSpecific_STM32F4.h` -> `Nuvoton8051PlatformSpecific.h` (remove `_STM32F4` suffix from name)
5) Include library into your app using `#include "Nuvoton8051.h"`
6) Write and test your application code. See examples bellow.

## Raspberry Pi
There are also provided implementation that could run on Raspberry Pi and many other single board computers running Linux, tak can control GPIO ports using `/sys/class/gpio`. File system. Note that you must diconnect any 5V power suply when connected to Raspberry Pi and power Nuvoton only by 3.3V max. Otherwise you burn your Raspberry Pi. Default pinout is following:

```
Nuvoton's    RST <------> GPIO2 (pin #1) on Raspberry Pi
Nuvoton's ICPCLK <------> GPIO3 (pin #3) on Raspberry Pi
Nuvoton's ICPDAT <------> GPIO4 (pin #5) on Raspberry Pi
```

If you want to use it do following:
1) Copy library to your project.
2) Delete all unnescessary files for other platforms like `Nuvoton8051PlatformSpecific_AVR.c` and `Nuvoton8051PlatformSpecific_AVR.h`. Only files `Nuvoton8051.c`, `Nuvoton8051.h`, `Nuvoton8051PlatformSpecific_RaspberryPi.c` and `Nuvoton8051PlatformSpecific_RaspberryPi.h` must be present.
3) Rename `Nuvoton8051PlatformSpecific_RaspberryPi.c` -> `Nuvoton8051PlatformSpecific.c` (remove `_RaspberryPi` suffix from name)
4) Rename `Nuvoton8051PlatformSpecific_RaspberryPi.h` -> `Nuvoton8051PlatformSpecific.h` (remove `_RaspberryPi` suffix from name)
5) Include library into your app using `#include "Nuvoton8051.h"`
6) Write and test your application code. See examples bellow.

Implementation also includes two additional functions. It is recommended use Nuvoton8051_RaspberryPiUninit() function after completing work. If you forget to call this function or your app crash before calling it you will became getting following error message if you run your app again.

```
/sys/class/gpio/gpio2 gpio pin is already exported.
```

In that case you need to unexport pin manually using following commands.

```
echo 2 > /sys/class/gpio/unexport
echo 3 > /sys/class/gpio/unexport
echo 4 > /sys/class/gpio/unexport
```

Then your app became to work again.

# Disclaimer

Library is provided without any warranty. Use it on your own risk.

# Examples

## Read CID, PID and DID of device
This is good point to start. Following code prints CID, DID and PID of device. It could be used as verification that connection and interface with device is working.

```
#include "Nuvoton8051.h"

int main(void) {
	Nuvoton8051_Init();
	Nuvoton8051_EntryMode();
	
	uint8_t cid = Nuvoton8051_ReadCID();
	uint16_t did = Nuvoton8051_ReadDID();
	uint16_t pid = Nuvoton8051_ReadPID();
		
	Nuvoton8051_ExitMode();
	
	// print cid, did and pid variable here.
	
	while (1) {
	}
}
```

## Read first 2048 bytes of program flash

```
#include "Nuvoton8051.h"

uint8_t buffer[2048];

int main(void) {
	Nuvoton8051_Init();
	Nuvoton8051_EntryMode();
	
	Nuvoton8051_ReadFlash(0, 2048, buffer);
	
	Nuvoton8051_ExitMode();
	
	// print content of buffer
	
	while (1) {
	}
}
```

## Erase device and write content of buffer to program flash

```
#include "Nuvoton8051.h"

int main(void) {
	uint8_t program[8192];
	
	// load your binary into program buffer

	Nuvoton8051_Init();
	Nuvoton8051_EntryMode();

	Nuvoton8051_MassErase();
	Nuvoton8051_ProgramFlash(0, 8192, program, 1);
	
	Nuvoton8051_ExitMode();

	while (1) {
	}
}
```

# Questions?
If you have any question you can ask simply by creating issue.