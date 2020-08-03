
#define F_CPU 8000000 // Clock Speed
#define BAUD 9600
#define UBRR_VALUE F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART_irq.h"
#include <util/delay.h>
#include <stdio.h>



static FILE this_stdout = FDEV_SETUP_STREAM(USART_Transmit_IO, USART_Receive_IO,  _FDEV_SETUP_WRITE);



int main(void)
{
	
	USART_Init(UBRR_VALUE); //Calculate baud rate
	sei();
	
	stdin=stdout=&this_stdout;
	
	//char receivedString[USART_RX_BUFFER_SIZE];
	uint8_t u8Data;
	while(1)
	{
		USART_Transmit(USART_Receive());
		/*
		printf("\nPress any key:");
		//scan standard stream (USART)
		scanf("%c",&u8Data);
		printf("\nYou pressed: ");
		//print scanned character and its code
		printf("%c; Key code: %u",u8Data, u8Data);
		//printf("\nEnter a string and press Return:");
		//gets(&receivedString);
		//printf("\nYou entered:'%s'",receivedString);
		*/
	}
	
	return 0;
}








