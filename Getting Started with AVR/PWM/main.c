/*
* AVR_GPIO.c
*
* Created: 08/07/2020 20:28:18
* Author : John
*/

//#pragma GCC optimize ("O0") //Enable for simulator local variable debugging

//Using timer interrupts

#define F_CPU 8000000UL //8Mhz assumes fuse CKDIV8 set low

#include <avr/io.h>
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
	LED_PB0_ON;
}

ISR(TIMER1_COMPB_vect)
{
	LED_PB0_OFF;
}


//void PWM_Initialise(uint16_t freqHzCompA, uint16_t freqHzCompB)
//{
	//TCCR1B |= (1<<CS10) | (1<<WGM12); // Timer/Counter Control Register B = No prescaler) |  Clear Timer on Compare match (CTC) mode
	//TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B); //Timer/Counter1 Interrupt Mask Register = Bit 1 – OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable | Bit 2 – OCIE1B: Timer/Counter1, Output Compare B Match Interrupt Enable
	//
	////Max pulse length = 65536 (16 bit register size) / 8 Mhz (max clock speed) = 0.008192s (no prescaler). 
	////Min Frequency = 122Hz (with OCR1A/OCR1B set to 0xFFFF)
	////Max frequency = 8Mhz (with OCR1A/OCR1B set to 0x0001) 
	//OCR1A = (F_CPU/freqHzCompA) -1; //Output Compare Registers = F_CPU/frequency*N-1 //see 18.7.2 Clear Timer on Compare Match (CTC) Mode in datasheet
	//OCR1B = (F_CPU/freqHzCompB) -1; //Output Compare Registers = F_CPU/frequency*N-1 //see 18.7.2 Clear Timer on Compare Match (CTC) Mode in datasheet
//}

//dutyCyclePercentage between 0 and 100
//BUG for 0 and >=100%
void PWM_Initialise(uint8_t dutyCyclePercentage)
{
	TCCR1B |= (1<<CS10) | (1<<WGM12); // Timer/Counter Control Register B = No prescaler) |  Clear Timer on Compare match (CTC) mode
	TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B); //Timer/Counter1 Interrupt Mask Register = Bit 1 – OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable | Bit 2 – OCIE1B: Timer/Counter1, Output Compare B Match Interrupt Enable
	
	uint16_t comp = 800; //10Khz  (F_CPU/freqHzCompA) 
	uint16_t compA = comp;
	uint16_t compB =  (dutyCyclePercentage/100.0) * comp;
	
	//these don't quite work
	if (dutyCyclePercentage == 0)
	{
		compA=comp;
		compB=0;
	}
	//these don't quite work
	if (dutyCyclePercentage >=100)
	{
		compA=comp;
		compB=comp;
	}
	
	//Max pulse length = 65536 (16 bit register size) / 8 Mhz (max clock speed) = 0.008192s (no prescaler).
	//Min Frequency = 122Hz (with OCR1A/OCR1B set to 0xFFFF)
	//Max frequency = 8Mhz (with OCR1A/OCR1B set to 0x0001)
	//OCR1A= 1 = 8Mhz
	//OCR1A= 2 = 4Mhz
	//OCR1A= 100 = 800Khz, //OCR1A= 400 = 200Khz,//OCR1A= 800 = 100Khz
	
	//The TOP value is the value stored in the OCR1A Register. Reaching it will cause the counter to reset
	OCR1A = compA; //ON: Output Compare Registers = F_CPU/frequency*N-1 //see 18.7.2 Clear Timer on Compare Match (CTC) Mode in datasheet
	OCR1B = compB; //OFF: Output Compare Registers = F_CPU/frequency*N-1 //see 18.7.2 Clear Timer on Compare Match (CTC) Mode in datasheet
	
	//Larger OCR1B is compared to OCR1A, the larger the duty cycle. The Off frequency is reducing as OCR1B increases.
}


int main(void)
{
	
	
	
	DDRB |= (1<<DDB0); // Data direction register - Set PB0 high for output
	DDRB &= ~(1<<DDB7); //Data direction register - Set PB7 low for input
	
	
	//PWM_Initialise(12); //12% Duty Cycle
	//PWM_Initialise(6); //6% Duty Cycle
	//PWM_Initialise(1); //1% Duty Cycle
	//PWM_Initialise(25); //25% Duty Cycle
	//PWM_Initialise(50); //50% Duty Cycle
	//PWM_Initialise(75); //75% Duty Cycle
	
	//PWM_Initialise(100); //100% Duty Cycle //these don't quite work
	//PWM_Initialise(0); //0% Duty Cycle  //these don't quite work
	
	PWM_Initialise(75); 
	

	sei(); //Enable interrupts by setting the global interrupt mask
	
	while (1)
	{
		
	}

}
