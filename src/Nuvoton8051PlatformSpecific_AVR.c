#include "Nuvoton8051PlatformSpecific.h"

void Nuvoton8051_GpioInit() {
	NU8051_RST_DDR_REG |= NU8051_RST_PIN_MASK;
	NU8051_DAT_DDR_REG |= NU8051_DAT_PIN_MASK;
	NU8051_CLK_DDR_REG |= NU8051_CLK_PIN_MASK;
}


void Nuvoton8051_DelayUs(uint32_t periodUs) {
	_delay_us(50 * periodUs);
}

void Nuvoton8051_GpioSetRstState(uint32_t level) {
	if (level) {
		NU8051_RST_PORT_REG |= NU8051_RST_PIN_MASK;
	} else {
		NU8051_RST_PORT_REG &= ~NU8051_RST_PIN_MASK;
	}
}

void Nuvoton8051_GpioSetClkState(uint32_t level) {
	if (level) {
		NU8051_CLK_PORT_REG |= NU8051_CLK_PIN_MASK;
	} else {
		NU8051_CLK_PORT_REG &= ~NU8051_CLK_PIN_MASK;
	}
}

void Nuvoton8051_GpioSetDatState(uint32_t level) {
	if (level) {
		NU8051_DAT_PORT_REG |= NU8051_DAT_PIN_MASK;
	} else {
		NU8051_DAT_PORT_REG &= ~NU8051_DAT_PIN_MASK;
	}
}

uint32_t Nuvoton8051_GpioGetDatState() {
	return !!(NU8051_DAT_PIN_REG & NU8051_DAT_PIN_MASK);
}

void Nuvoton8051_GpioSetDatAsInput() {
	NU8051_DAT_DDR_REG &= ~NU8051_DAT_PIN_MASK;
}

void Nuvoton8051_GpioSetDatAsOutput() {
	NU8051_DAT_DDR_REG |= NU8051_DAT_PIN_MASK;
}
