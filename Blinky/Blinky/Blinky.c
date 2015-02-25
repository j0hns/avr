/*
* Blinky.c
*
* Created: 24/02/2015 21:35:18
*  Author: John
*/

#define F_CPU 1000000L

#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
	DDRB |= (1 <<PB0); //Data Direction Register B: Writing a one to the bit enables output.
	while(1)
	{
		PORTB= 0b00000001; //Turn on first LED pin in PORTB
		_delay_ms(15);
		
		PORTB = 0b00000000; // And turn off
		_delay_ms(15);
		
		
	
	}
	
	return 0;
}