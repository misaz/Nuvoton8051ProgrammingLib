#include "Nuvoton8051.h"
#include "Nuvoton8051PlatformSpecific.h"

uint32_t programFlashWriteDelay = 20;
uint32_t erasePageDelay = 5000;

static void Nuvoton8051_WriteBits(uint32_t value, uint8_t bits_count) {
	for (int i = 0; i < bits_count; i++) {
		Nuvoton8051_GpioSetDatState((value >> (bits_count - i - 1)) & 1);
		Nuvoton8051_DelayUs(1);
		Nuvoton8051_GpioSetClkState(1);
		Nuvoton8051_DelayUs(1);
		Nuvoton8051_GpioSetClkState(0);
	}
}

static void Nuvoton8051_SendCommand(uint32_t command, uint32_t param) {
	Nuvoton8051_WriteBits(command | (param << 6), 24);
}

static uint8_t Nuvoton8051_ReadData(uint32_t isLastTransfer) { // pin_value = (bool)isLastTransfer
	uint8_t result = 0;

	Nuvoton8051_GpioSetDatAsInput();
	Nuvoton8051_DelayUs(1);

	for (int i = 0; i < 8; i++) {
		uint8_t pinStatus;
		Nuvoton8051_DelayUs(1);

		pinStatus = Nuvoton8051_GpioGetDatState();

		Nuvoton8051_GpioSetClkState(1);
		Nuvoton8051_DelayUs(1);
		Nuvoton8051_GpioSetClkState(0);

		result |= pinStatus << (7 - i);
	}

	Nuvoton8051_GpioSetDatAsOutput();

	Nuvoton8051_GpioSetDatState(!!isLastTransfer);
	Nuvoton8051_DelayUs(1);

	Nuvoton8051_GpioSetClkState(1);
	Nuvoton8051_DelayUs(1);

	Nuvoton8051_GpioSetDatState(0);
	Nuvoton8051_GpioSetClkState(0);

	return result;
}

static void Nuvoton8051_WriteData(uint8_t value, uint32_t isLastTransfer, uint32_t delayTime1, uint32_t delayTime2) {
	Nuvoton8051_WriteBits(value, 8);

	Nuvoton8051_GpioSetDatState(!!isLastTransfer);
	Nuvoton8051_DelayUs(delayTime1);

	Nuvoton8051_GpioSetClkState(1);
	Nuvoton8051_DelayUs(delayTime2);

	Nuvoton8051_GpioSetClkState(0);
	Nuvoton8051_GpioSetDatState(0);
}

void Nuvoton8051_Init() {
	Nuvoton8051_GpioInit();

	Nuvoton8051_GpioSetClkState(0);
	Nuvoton8051_GpioSetDatState(0);
	Nuvoton8051_GpioSetRstState(1);
}

void Nuvoton8051_MassErase() {
	Nuvoton8051_SendCommand(38, 0x3a5a5);
	Nuvoton8051_WriteData(255, 1, 50000, 500);
}

uint32_t Nuvoton8051_ReadFlash(uint32_t address, uint32_t size, uint8_t *buffer) {
	if (size == 0) {
		return -1;
	}

	Nuvoton8051_SendCommand(0, address);

	for (int i = 0; i < size; i++) {
		buffer[i] = Nuvoton8051_ReadData(i == size - 1);
	}

	return address + size;
}

uint32_t Nuvoton8051_ProgramFlash(uint32_t address, uint32_t size, uint8_t* buffer, uint32_t verify) {
	if (size == 0) {
		return -1;
	}

	Nuvoton8051_SendCommand(33, address);
	for (int i = 0; i < size; i++) {
		Nuvoton8051_WriteData(buffer[i], i == size - 1, programFlashWriteDelay, 5);
	}

	if (verify) {
		Nuvoton8051_SendCommand(0, address);

		for (int i = 0; i < size; i++) {
			if (buffer[i] != Nuvoton8051_ReadData(i == size - 1)) {
				return address + i;
			}
		}
	}

	return address + size;
}

void Nuvoton8051_EraseFlashPage(uint32_t address) {
	Nuvoton8051_SendCommand(34, address);
	Nuvoton8051_WriteData(255, 1, erasePageDelay, 100);
}

uint32_t Nuvoton8051_ReadSPROM(uint32_t address, uint32_t size, uint8_t* buffer) {
	return Nuvoton8051_ReadFlash(address + 0x1800002, size, buffer) - 0x1800002;
}

uint32_t Nuvoton8051_ProgramSPROM(uint32_t address, uint32_t size, uint8_t* buffer, uint32_t verify) {
	return Nuvoton8051_ProgramFlash(address + 0x1800002, size, buffer, verify) - 0x1800002;
}

void Nuvoton8051_EraseSPROM(void) {
	Nuvoton8051_EraseFlashPage(0x1800002);
}

uint32_t Nuvoton8051_ReadCFG(uint8_t *buffer) {
	return Nuvoton8051_ReadFlash(0x30000, 5, buffer);
}

uint32_t Nuvoton8051_ProgramCFG(uint8_t* buffer) {
	if (buffer == NULL) {
		return 0;
	}

	// overwriting 3rd config byte disables watchdog, it is done becase reversed liubrary also does this.
	buffer[3] = 0xFF;
	return Nuvoton8051_ProgramFlash(0x30000, 5, buffer, 0);
}

void Nuvoton8051_EraseCFG() {
	Nuvoton8051_EraseFlashPage(0x30000);
}

void Nuvoton8051_EntryMode() {
	Nuvoton8051_DelayUs(200);

	for (int i = 0; i < 25; i++) {
		Nuvoton8051_GpioSetRstState((0x9e1cb6 >> (24 - i)) & 1);
		Nuvoton8051_DelayUs(100);
	}

	Nuvoton8051_DelayUs(100);
	Nuvoton8051_WriteBits(0x5aa503, 24);
	Nuvoton8051_DelayUs(10);

	if (Nuvoton8051_ReadDID() == 47) {
		erasePageDelay = 40000;
		programFlashWriteDelay = 40;
	} else {
		erasePageDelay = 5000;
		programFlashWriteDelay = 20;
	}
}

void Nuvoton8051_ExitMode() {
	Nuvoton8051_DelayUs(10);

	Nuvoton8051_GpioSetRstState(1);
	Nuvoton8051_DelayUs(5000);

	Nuvoton8051_GpioSetRstState(0);
	Nuvoton8051_DelayUs(1000);
	Nuvoton8051_DelayUs(10000);

	Nuvoton8051_WriteBits(0x0f78f0, 24);
	Nuvoton8051_DelayUs(500);

	Nuvoton8051_GpioSetRstState(1);
}

uint16_t Nuvoton8051_ReadDID() {
	Nuvoton8051_SendCommand(12, 0);

	uint16_t lsb = Nuvoton8051_ReadData(0);
	uint16_t msb = Nuvoton8051_ReadData(1);

	return lsb | (msb << 8);
}

uint16_t Nuvoton8051_ReadPID() {
	Nuvoton8051_SendCommand(12, 2);

	uint16_t lsb = Nuvoton8051_ReadData(0);
	uint16_t msb = Nuvoton8051_ReadData(1);

	return lsb | (msb << 8);
}

uint8_t Nuvoton8051_ReadCID() {
	Nuvoton8051_SendCommand(11, 0);
	return Nuvoton8051_ReadData(1);
}

