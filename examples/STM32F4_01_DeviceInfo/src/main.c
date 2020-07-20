#include "Nuvoton8051.h"

int main(void) {
	Nuvoton8051_Init();
	Nuvoton8051_EntryMode();

	uint8_t cid = Nuvoton8051_ReadCID();
	uint16_t did = Nuvoton8051_ReadDID();
	uint16_t pid = Nuvoton8051_ReadPID();

	Nuvoton8051_ExitMode();

	// stop program using debugger at while (1) { line and see content of variables in debugger.
	// if you do not have debugger add some UART printing or similar logic here.

	while (1) {
	}
}
