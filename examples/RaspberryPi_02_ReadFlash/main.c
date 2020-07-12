#include "Nuvoton8051.h"
#include "Nuvoton8051PlatformSpecific.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BUFF_LEN 8192

int main(void) {
	uint8_t program[BUFF_LEN];

	// open firmware file
	FILE* fFirmware = fopen("firmware_read.bin", "wb");
	if (fFirmware == NULL) {
		printf("I/O error while opening firmware_read.bin file. Error %d (%s).\n", errno, strerror(errno));
		return 1;
	}

	Nuvoton8051_Init();
	Nuvoton8051_EntryMode();

	Nuvoton8051_ReadFlash(0, BUFF_LEN, program);

	Nuvoton8051_ExitMode();
	Nuvoton8051_RaspberryPiUninit();

	// write firmware to output file
	if (fwrite(program, 1, BUFF_LEN, fFirmware) != BUFF_LEN) {
		printf("I/O error while writing firmware_read.bin file. Error %d (%s).\n", errno, strerror(errno));
		return 1;
	}

	// close file
	if (fclose(fFirmware) != 0) {
		printf("I/O error while closing firmware.bin file.\n");
		return 1;
	}

	return 0;
}