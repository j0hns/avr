
#define F_CPU 8000000 // Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART_irq.h"
#include <util/delay.h>
#include <stdio.h>

char helloWorldString[]="Hello World!!";


static FILE this_stdout = FDEV_SETUP_STREAM(USART_Transmit_IO, USART_Receive_IO,  _FDEV_SETUP_WRITE);

int main(void)
{
	
	USART_Init(MYUBRR); //Calculate baud rate
	sei();
	
	stdin=stdout=&this_stdout;
	
	uint16_t u16Data = 10;

	for( ; ; ) {
		/* Echo the received character */
		//USART_Transmit(USART_Receive());
		USART_TransmitString(helloWorldString);
		printf("\nunsigned int = %u",u16Data);
		_delay_ms(1000);
	}
	
	return 0;
}






