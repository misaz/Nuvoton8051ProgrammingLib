#include "Nuvoton8051PlatformSpecific.h"

void Nuvoton8051_GpioInit() {
	RCC_AHB1PeriphClockCmd(NU8051_RST_GPIO_RCC_AHB1Periph, ENABLE);
	RCC_AHB1PeriphClockCmd(NU8051_DAT_GPIO_RCC_AHB1Periph, ENABLE);
	RCC_AHB1PeriphClockCmd(NU8051_CLK_GPIO_RCC_AHB1Periph, ENABLE);

	// setup GPIO
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_25MHz;

	// setup GPIO pin RST
	gpio.GPIO_Pin = NU8051_RST_GPIO_Pin;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(NU8051_RST_GPIO, &gpio);

	// setup GPIO pin DAT
	gpio.GPIO_Pin = NU8051_DAT_GPIO_Pin;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(NU8051_DAT_GPIO, &gpio);

	// setup GPIO pin CLK
	gpio.GPIO_Pin = NU8051_CLK_GPIO_Pin;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(NU8051_CLK_GPIO, &gpio);
}

void Nuvoton8051_DelayUs(uint32_t periodUs) {
	SysTick->LOAD = SystemCoreClock / 1000000UL * periodUs;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;

	while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)) {
	}

	SysTick->CTRL = 0;
}

void Nuvoton8051_GpioSetRstState(uint32_t level) {
	GPIO_WriteBit(NU8051_RST_GPIO, NU8051_RST_GPIO_Pin, level);
}

void Nuvoton8051_GpioSetClkState(uint32_t level) {
	GPIO_WriteBit(NU8051_CLK_GPIO, NU8051_CLK_GPIO_Pin, level);
}

void Nuvoton8051_GpioSetDatState(uint32_t level) {
	GPIO_WriteBit(NU8051_DAT_GPIO, NU8051_DAT_GPIO_Pin, level);
}

uint32_t Nuvoton8051_GpioGetDatState() {
	return GPIO_ReadInputDataBit(NU8051_DAT_GPIO, NU8051_DAT_GPIO_Pin);
}

void Nuvoton8051_GpioSetDatAsInput() {
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_25MHz;
	gpio.GPIO_Pin = NU8051_DAT_GPIO_Pin;

	// set GPIO DAT as input
	GPIO_Init(NU8051_DAT_GPIO, &gpio);
}

void Nuvoton8051_GpioSetDatAsOutput() {
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_25MHz;
	gpio.GPIO_Pin = NU8051_DAT_GPIO_Pin;

	// set GPIO DAT as input
	GPIO_Init(NU8051_DAT_GPIO, &gpio);
}
