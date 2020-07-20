#include "Nuvoton8051.h"
#include "blink.h"
#include <avr/io.h>

int main(void) {
	Nuvoton8051_Init();
	Nuvoton8051_EntryMode();

	Nuvoton8051_MassErase();
	Nuvoton8051_ProgramFlash(0, blink_bin_len, blink_bin, 1);
	
	Nuvoton8051_ExitMode();

	DDRB |= 1;
	PORTB &= ~(1);

	while (1) {
	}
}