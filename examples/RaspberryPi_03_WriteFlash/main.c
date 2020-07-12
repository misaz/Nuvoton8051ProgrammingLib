#include "Nuvoton8051.h"
#include "Nuvoton8051PlatformSpecific.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(void) {
	// open firmware file
	FILE* fFirmware = fopen("firmware.bin", "rb");
	if (fFirmware == NULL) {
		printf("I/O error while opening firmware.bin file. Error %d (%s).\n", errno, strerror(errno));
		return 1;
	}

	// seek to end to determine file size
	if (fseek(fFirmware, 0, SEEK_END) != 0) {
		printf("I/O error while seeking firmware.bin file. Error %d (%s).\n", errno, strerror(errno));
		return 1;
	}

	// load length from current position
	long int length;
	if ((length = ftell(fFirmware)) == -1L) {
		printf("I/O error while telling position in firmware.bin file. Error %d (%s).\n", errno, strerror(errno));
		return 1;
	}

	// seek back to start of file
	if (fseek(fFirmware, 0, SEEK_SET) != 0) {
		printf("I/O error while seeking firmware.bin file. Error %d (%s).\n", errno, strerror(errno));
		return 1;
	}
	
	// allocated buffer for firmware
	uint8_t* program = (uint8_t*)malloc(length);
	if (program == NULL) {
		printf("Out of memory.\n");
		return 1;
	}

	// read firmware from file to buffer
	if (fread(program, 1, length, fFirmware) != length) {
		printf("I/O error while reading firmware.bin file. Error %d (%s).\n", errno, strerror(errno));
		return 1;
	}

	// close file
	if (fclose(fFirmware) != 0) {
		printf("I/O error while closing firmware.bin file.\n");
		return 1;
	}

	Nuvoton8051_Init();
	Nuvoton8051_EntryMode();

	Nuvoton8051_MassErase();
	Nuvoton8051_ProgramFlash(0, length, program, 1);

	Nuvoton8051_ExitMode();
	Nuvoton8051_RaspberryPiUninit();

	free(program);

	return 0;
}