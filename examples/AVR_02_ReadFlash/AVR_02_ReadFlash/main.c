#include "Nuvoton8051.h"
#include <avr/io.h>
#include <string.h>

uint8_t buffer[128];

void UART_Init() {
	UBRR1H = 0;
	UBRR1L = 103;
	UCSR1B |= (1<<TXEN1);
	UCSR1C |= (1<<UCSZ10) | (1<<UCSZ11);
}

void UART_PrintString(char* message) {
	for (int i = 0; i < strlen(message); i++) {
		while (!(UCSR1A & (1<<UDRE1)));
		UDR1 = message[i];
	}
}

void UART_PrintNumberHex2(int number) {
	unsigned char buff[9];
	itoa(number, buff, 16);
	if (strlen(buff) == 1) {
		UART_PrintString("0");
	}
	UART_PrintString(buff);
}

void UART_PrintBuffer(uint8_t* buffer, size_t length) {
	for (int i = 0; i < 128; i++) {
		UART_PrintNumberHex2(buffer[i]);
		UART_PrintString(" ");
		
		if (i % 16 == 15) {
			UART_PrintString("\r\n");
		}
	}
}

int main(void) {
	UART_Init();
	UART_PrintString("Flash content:\r\n");
	
	Nuvoton8051_Init();
	Nuvoton8051_EntryMode();
	
	// reads flash per 128 B blocks because of limited AVR RAM size.
	for (int i = 0; i < 16; i++) {
		Nuvoton8051_ReadFlash(i * 128, 128, buffer);
		UART_PrintBuffer(buffer, 128);
	}
	
	Nuvoton8051_ExitMode();
	
	while (1) {
	}
}