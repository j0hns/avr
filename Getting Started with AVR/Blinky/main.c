/*
 * Blinky.c
 *
 * Created: 07/07/2020 21:24:13
 * Author : John
 */ 
#define F_CPU 8000000UL //8Mhz assumes fuse CKDIV8 set low

#include <avr/io.h>
#include <util/delay.h> 

//for use with OneDrive\Documents\Maker\AVR ISP Programmer\ZIF Programmer.fzz
//Led on pin 14 = PB0

//use macros to make it more readable
#define LED_PB0_ON		PORTB |= (1<<PORTB0);//set pin 14 (PB0) high - switch on
#define LED_PB0_TOGGLE	PINB |= (1<<PINB0); //toggle PB0

int main(void)
{
	
    DDRB = (1<<DDB0); // Data direction register - Set PB0 high for output
	
	LED_PB0_ON;
	
    while (1) 
    {
		LED_PB0_TOGGLE;
		_delay_ms(500);
    }
}

