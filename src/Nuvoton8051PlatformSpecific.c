#include "Nuvoton8051PlatformSpecific.h"

void Nuvoton8051_GpioInit() {
	// init GPIO ports for RST, CLK and DAT pin to OUTPUT mode
}


void Nuvoton8051_DelayUs(uint32_t periodUs) {
	// while function is named DelayUs is better to delay aprox 20 - 50 us instead.
	// remember to multiple wait time with parameter.
}

void Nuvoton8051_GpioSetRstState(uint32_t level) {
	// set RST pin to logical HIGH if level is nonzero, to LOW otherwise
}

void Nuvoton8051_GpioSetClkState(uint32_t level) {
	// set CLK pin to logical HIGH if level is nonzero, to LOW otherwise
}

void Nuvoton8051_GpioSetDatState(uint32_t level) {
	// set DAT pin to logical HIGH if level is nonzero, to LOW otherwise
}

uint32_t Nuvoton8051_GpioGetDatState() {
	// return 1 if DAT pin is read as logical HIGH, 0 if it read as logical LOW. 
	// This function will be called only when pin was set as input using 
	// Nuvoton8051_GpioSetDatAsInput function by library.
}

void Nuvoton8051_GpioSetDatAsInput() {
	// set DAT pin to INPUT mode
}

void Nuvoton8051_GpioSetDatAsOutput() {
	// set DAT pin to OUTPUT mode
}
