#include "Nuvoton8051.h"
#include "Nuvoton8051PlatformSpecific.h"

#include <stdio.h>

int main(void) {
	Nuvoton8051_Init();
	Nuvoton8051_EntryMode();

	uint8_t cid = Nuvoton8051_ReadCID();
	uint16_t did = Nuvoton8051_ReadDID();
	uint16_t pid = Nuvoton8051_ReadPID();

	Nuvoton8051_ExitMode();
	Nuvoton8051_RaspberryPiUninit();

	printf("Device informations: \nCID: 0x%02X\nDID: 0x%04X\nPID: 0x%04X\n", cid, did, pid);

	return 0;
}