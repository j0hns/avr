/*
* AVR_GPIO.c
*
* Created: 08/07/2020 20:28:18
* Author : John
*/

#define F_CPU 8000000UL //8Mhz assumes fuse CKDIV8 set low

#include <avr/io.h>
#include <util/delay.h>


//Led on pin 14 = PB0
//switch on pin 10 = PB7

//use macros to make it more readable
#define LED_PB0_ON		PORTB |= (1<<PORTB0);//set pin 14 (PB0) high - led on
#define LED_PB0_OFF		PORTB &= ~(1<<PORTB0);//set pin 14 (PB0) low - led off
#define LED_PB0_TOGGLE	PINB |= (1<<PINB0); //toggle PB0

int main(void)
{
	
	PORTB |= (1<<PINB7); //initialise pull up resistor on input pin
	DDRB |= (1<<DDB0); // Data direction register - Set PB0 high for output
	DDRB &= ~(1<<DDB7); //Data direction register - Set PB7 low for input
	
	while (1)
	{
		if (!(PINB & (1<<PINB7))) //If PINB7 is low
		{
			LED_PB0_ON;
		}
		else
		{
			LED_PB0_OFF
		}
		
	}

}
