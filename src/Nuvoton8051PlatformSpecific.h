#ifndef NUVOTON8051PLATFORMSPECIFIC_H_
#define NUVOTON8051PLATFORMSPECIFIC_H_

void Nuvoton8051_GpioInit();

void Nuvoton8051_DelayUs(uint32_t periodUs);

void Nuvoton8051_GpioSetRstState(uint32_t level);
void Nuvoton8051_GpioSetClkState(uint32_t level);
void Nuvoton8051_GpioSetDatState(uint32_t level);

uint32_t Nuvoton8051_GpioGetDatState();

void Nuvoton8051_GpioSetDatAsInput();
void Nuvoton8051_GpioSetDatAsOutput();

#endif
