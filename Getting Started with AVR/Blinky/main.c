/*
 * Blinky.c
 *
 * Created: 07/07/2020 21:24:13
 * Author : John
 */ 

#include <avr/io.h>

//for use with OneDrive\Documents\Maker\AVR ISP Programmer\ZIF Programmer.fzz

int main(void)
{
    DDRB = (1<<DDB0);
    while (1) 
    {
		//set pin 14 (PB0) high
		PORTB |= (1<<PORTB0);
    }
}

