#ifndef Nuvoton8051_H_
#define Nuvoton8051_H_

#include <stdint.h>

void Nuvoton8051_Init();

void Nuvoton8051_EntryMode();
void Nuvoton8051_ExitMode();

void Nuvoton8051_MassErase();

uint32_t Nuvoton8051_ReadFlash(uint32_t address, uint32_t size, uint8_t* buffer);
uint32_t Nuvoton8051_ProgramFlash(uint32_t address, uint32_t size, uint8_t* buffer, uint32_t verify);
void Nuvoton8051_EraseFlashPage(uint32_t address);

uint32_t Nuvoton8051_ReadSPROM(uint32_t address, uint32_t size, uint8_t* buffer);
uint32_t Nuvoton8051_ProgramSPROM(uint32_t address, uint32_t size, uint8_t* buffer, uint32_t verify);
void Nuvoton8051_EraseSPROM(void);

uint32_t Nuvoton8051_ReadCFG(uint8_t* buffer);
uint32_t Nuvoton8051_ProgramCFG(uint8_t* buffer);
void Nuvoton8051_EraseCFG();

uint16_t Nuvoton8051_ReadDID();
uint16_t Nuvoton8051_ReadPID();
uint8_t Nuvoton8051_ReadCID();
uint32_t Nuvoton8051_ReadCFG(uint8_t* buffer);

/*
 PRIVATE:
 void Nuvoton8051_SendCommand(uint32_t command, uint32_t shift6);
 void Nuvoton8051_WriteBits(uint32_t value, uint8_t bits_count);
 uint8_t Nuvoton8051_ReadData(uint32_t isLastTransfer);
 void Nuvoton8051_WriteData(uint8_t value, uint32_t isLastTransfer, uint32_t delayTime1, uint32_t delayTime2);
 */

#endif
