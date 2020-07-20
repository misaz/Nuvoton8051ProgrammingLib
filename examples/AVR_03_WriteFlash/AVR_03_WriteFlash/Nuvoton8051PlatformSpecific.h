#ifndef NUVOTON8051PLATFORMSPECIFIC_H_
#define NUVOTON8051PLATFORMSPECIFIC_H_

#define __DELAY_BACKWARD_COMPATIBLE__

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define NU8051_RST_DDR_REG              DDRD
#define NU8051_RST_PORT_REG             PORTD
#define NU8051_RST_PIN_REG              PIND
#define NU8051_RST_PIN_NUM              1
#define NU8051_RST_PIN_MASK             (1 << NU8051_RST_PIN_NUM)

#define NU8051_DAT_DDR_REG              DDRD
#define NU8051_DAT_PORT_REG             PORTD
#define NU8051_DAT_PIN_REG              PIND
#define NU8051_DAT_PIN_NUM              0
#define NU8051_DAT_PIN_MASK             (1 << NU8051_DAT_PIN_NUM)

#define NU8051_CLK_DDR_REG              DDRD
#define NU8051_CLK_PORT_REG             PORTD
#define NU8051_CLK_PIN_REG              PIND
#define NU8051_CLK_PIN_NUM              4
#define NU8051_CLK_PIN_MASK             (1 << NU8051_CLK_PIN_NUM)

void Nuvoton8051_GpioInit();

void Nuvoton8051_DelayUs(uint32_t periodUs);

void Nuvoton8051_GpioSetRstState(uint32_t level);
void Nuvoton8051_GpioSetClkState(uint32_t level);
void Nuvoton8051_GpioSetDatState(uint32_t level);

uint32_t Nuvoton8051_GpioGetDatState();

void Nuvoton8051_GpioSetDatAsInput();
void Nuvoton8051_GpioSetDatAsOutput();


#endif
