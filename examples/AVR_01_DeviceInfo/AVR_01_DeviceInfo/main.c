#include "Nuvoton8051.h"
#include <avr/io.h>

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

void UART_PrintNumberHex(int number) {
	unsigned char buff[9];
	itoa(number, buff, 16);
	UART_PrintString(buff);
}

int main(void) {
	UART_Init();
	
	Nuvoton8051_Init();
	Nuvoton8051_EntryMode();
	
	uint8_t cid = Nuvoton8051_ReadCID();
	uint16_t did = Nuvoton8051_ReadDID();
	uint16_t pid = Nuvoton8051_ReadPID();
	
	Nuvoton8051_ExitMode();
	
	UART_PrintString("Device informations:\r\n");
	UART_PrintString("CID: 0x");
	UART_PrintNumberHex(cid);
	UART_PrintString("\r\nDID: 0x");
	UART_PrintNumberHex(did);
	UART_PrintString("\r\nPID: 0x");
	UART_PrintNumberHex(pid);
	UART_PrintString("\r\n");
	
	while (1) {
	}
}