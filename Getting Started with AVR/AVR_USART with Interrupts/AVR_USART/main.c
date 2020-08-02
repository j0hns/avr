
#define F_CPU 8000000 // Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART_irq.h"
#include <util/delay.h>

char helloWorldString[]="Hello World!!";

int main(void)
{
	
	USART_Init(MYUBRR); //Calculate baud rate
	sei();

	for( ; ; ) {
		/* Echo the received character */
		//USART_Transmit(USART_Receive());
		USART_TransmitString(helloWorldString);
		_delay_ms(1000);
	}
	
	return 0;
}






