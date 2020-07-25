/*
* AVR_GPIO.c
*
* Created: 08/07/2020 20:28:18
* Author : John
*/

//Using timer interrupts

#define F_CPU 8000000UL //8Mhz assumes fuse CKDIV8 set low

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


//Led on pin 14 = PB0
//switch on pin 10 = PB7 => (PCINT7/XTAL2/TOSC2) PB7

//use macros to make it more readable
#define LED_PB0_ON		PORTB |= (1<<PORTB0)//set pin 14 (PB0) high - led on
#define LED_PB0_OFF		PORTB &= ~(1<<PORTB0)//set pin 14 (PB0) low - led off
#define LED_PB0_TOGGLE	PINB |= (1<<PINB0) //toggle PB0
#define SWITCH_PRESSED !(PINB & (1<<PINB7)) //True if PINB7 is low

ISR(TIMER1_COMPA_vect)
{
	LED_PB0_TOGGLE;
}

void Set_Timer1_Interrupt_Frequency(uint8_t freqHz)
{
	TCCR1B |= (1<<CS12) | (1<<WGM12); // Timer/Counter Control Register B = clkI/O/256 (From prescaler) |  Clear Timer on Compare match (CTC) mode
	TIMSK1 |= (1<<OCIE1A); //Timer/Counter1 Interrupt Mask Register = Bit 1 – OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable
	OCR1A = (F_CPU/(freqHz * 256) -1); //Output Compare Registers = F_CPU/frequency*2*N-1 //see 18.7.2 Clear Timer on Compare Match (CTC) Mode in datasheet
}

int main(void)
{
	
	
	
	DDRB |= (1<<DDB0); // Data direction register - Set PB0 high for output
	DDRB &= ~(1<<DDB7); //Data direction register - Set PB7 low for input
	
	Set_Timer1_Interrupt_Frequency(1);

	sei(); //Enable interrupts by setting the global interrupt mask
	
	while (1)
	{
		
	}

}
