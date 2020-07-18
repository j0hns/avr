/*
* AVR_GPIO.c
*
* Created: 08/07/2020 20:28:18
* Author : John
*/

//Using pin interrupts

#define F_CPU 8000000UL //8Mhz assumes fuse CKDIV8 set low

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


//Led on pin 14 = PB0
//switch on pin 10 = PB7 => (PCINT7/XTAL2/TOSC2) PB7

//use macros to make it more readable
#define LED_PB0_ON		PORTB |= (1<<PORTB0)//set pin 14 (PB0) high - led on
#define LED_PB0_OFF		PORTB &= ~(1<<PORTB0)//set pin 14 (PB0) low - led off
#define LED_PB0_TOGGLE	PINB |= (1<<PINB0) //toggle PB0
#define SWITCH_PRESSED !(PINB & (1<<PINB7)) //True if PINB7 is low

ISR(PCINT0_vect)
{
	if (SWITCH_PRESSED)
	{
		LED_PB0_ON;
	}
	else
	{
		LED_PB0_OFF;
	}
}

int main(void)
{
	
	
	PORTB |= (1<<PINB7); //initialise pull up resistor on input pin
	DDRB |= (1<<DDB0); // Data direction register - Set PB0 high for output
	DDRB &= ~(1<<DDB7); //Data direction register - Set PB7 low for input
	
	PRR = 0xFF; //Power Reduction register - now turn everything else off
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	
	//set up registers for interrupts on Pin 10 = PB7 => (PCINT7/XTAL2/TOSC2) 
	PCMSK0 |= (1<<PCINT7); //set Pin Change Mask Register 0 to enable interrupt on PINB7 = pin 10 = PB7 => (PCINT7/XTAL2/TOSC2)
	//When the PCIE0 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), pin change interrupt 0 is enabled. Any change on any enabled PCINT[7:0] pin will cause an interrupt [Data sheet]
	PCICR |= (1<<PCIE0); // Set Pin Change Interrupt Enabled
	sei(); //Enable interrupts by setting the global interrupt mask
	
	while (1)
	{
		sleep_mode();
	}

}
