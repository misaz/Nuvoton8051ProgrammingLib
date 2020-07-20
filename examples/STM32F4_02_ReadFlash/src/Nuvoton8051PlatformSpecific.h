#ifndef NUVOTON8051PLATFORMSPECIFIC_H_
#define NUVOTON8051PLATFORMSPECIFIC_H_

#include <stdlib.h>

#include "stm32f4xx.h"

#define NU8051_RST_GPIO                 GPIOG
#define NU8051_RST_GPIO_Pin             GPIO_Pin_2
#define NU8051_RST_GPIO_PinSource       GPIO_PinSource_2
#define NU8051_RST_GPIO_RCC_AHB1Periph  RCC_AHB1Periph_GPIOG

#define NU8051_CLK_GPIO                 GPIOD
#define NU8051_CLK_GPIO_Pin             GPIO_Pin_14
#define NU8051_CLK_GPIO_PinSource       GPIO_PinSource_14
#define NU8051_CLK_GPIO_RCC_AHB1Periph  RCC_AHB1Periph_GPIOD

#define NU8051_DAT_GPIO                 GPIOD
#define NU8051_DAT_GPIO_Pin             GPIO_Pin_12
#define NU8051_DAT_GPIO_PinSource       GPIO_PinSource_12
#define NU8051_DAT_GPIO_RCC_AHB1Periph  RCC_AHB1Periph_GPIOD


void Nuvoton8051_GpioInit();
void Nuvoton8051_DelayUs(uint32_t periodUs);

void Nuvoton8051_GpioSetRstState(uint32_t level);
void Nuvoton8051_GpioSetClkState(uint32_t level);
void Nuvoton8051_GpioSetDatState(uint32_t level);

uint32_t Nuvoton8051_GpioGetDatState();

void Nuvoton8051_GpioSetDatAsInput();
void Nuvoton8051_GpioSetDatAsOutput();


#endif
