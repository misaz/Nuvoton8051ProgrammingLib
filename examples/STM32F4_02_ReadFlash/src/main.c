#include "Nuvoton8051.h"

uint8_t buffer[2048];

int main(void) {
	Nuvoton8051_Init();
	Nuvoton8051_EntryMode();

	Nuvoton8051_ReadFlash(0, 2048, buffer);

	Nuvoton8051_ExitMode();

	// stop program using debugger at while (1) { line and see content of buffer in debugger.
	// if you do not have debugger add some UART printing or similar logic here.

	while (1) {
	}
}
