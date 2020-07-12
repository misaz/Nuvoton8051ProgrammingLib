#ifndef NUVOTON8051PLATFORMSPECIFIC_H_
#define NUVOTON8051PLATFORMSPECIFIC_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#define NU8051_RST_PIN_NUM 				"2"
#define NU8051_RST_PIN_FILE				"/sys/class/gpio/gpio2"
#define NU8051_RST_PIN_DIRECTION_FILE	"/sys/class/gpio/gpio2/direction"
#define NU8051_RST_PIN_VALUE_FILE		"/sys/class/gpio/gpio2/value"

#define NU8051_CLK_PIN_NUM 				"3"
#define NU8051_CLK_PIN_FILE				"/sys/class/gpio/gpio3"
#define NU8051_CLK_PIN_DIRECTION_FILE	"/sys/class/gpio/gpio3/direction"
#define NU8051_CLK_PIN_VALUE_FILE		"/sys/class/gpio/gpio3/value"

#define NU8051_DAT_PIN_NUM 				"4"
#define NU8051_DAT_PIN_FILE				"/sys/class/gpio/gpio4"
#define NU8051_DAT_PIN_DIRECTION_FILE	"/sys/class/gpio/gpio4/direction"
#define NU8051_DAT_PIN_VALUE_FILE		"/sys/class/gpio/gpio4/value"

void Nuvoton8051_GpioInit();

void Nuvoton8051_DelayUs(uint32_t periodUs);

void Nuvoton8051_GpioSetRstState(uint32_t level);
void Nuvoton8051_GpioSetClkState(uint32_t level);
void Nuvoton8051_GpioSetDatState(uint32_t level);

uint32_t Nuvoton8051_GpioGetDatState();

void Nuvoton8051_GpioSetDatAsInput();
void Nuvoton8051_GpioSetDatAsOutput();

void Nuvoton8051_RaspberryPiUnexportPins();
void Nuvoton8051_RaspberryPiUninit();

#endif
