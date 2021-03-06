/*
* TemperatureSender.cpp
*
* Created: 16/07/2015 17:36:51
*  Author: John


Hardware

TMP36 to Atmega ADC Connections
VCC -> 3.3V
VOUT-> ADC0/PC0(Pin 23)
GND -> GND
AVCC Needs reference voltage = 3.3v



TMP36
-40 to 150 C
Pin 1 - Power (2.7 - 5.5V) (0.05mA)
Pin 2 - Temp Voltage
Pin 3 - Gnd
*/

#define V_IN 3300L
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"

//RF 24 related includes
#include "SPI.h"
#include "nRF24L01.h"
#include "RF24.h"

extern "C" {
	#include "USART.h" //a C header, so wrap it in extern "C"
}



//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

const uint8_t cepin=9; //Arduino Pin 9 = ATMEGA168P Pin 15 = PB1
const uint8_t cspin=10;//Arduino Pin 10 = ATMEGA168P Pin 16 = PB2
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

RF24 radio(cepin,cspin);


// -------- Functions --------- //
static inline void initADC0(void) {
	//by default, it samples from PC0
	ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);     /* ADC clock prescaler /8 */
	ADCSRA |= (1 << ADEN);                                 /* enable ADC */
}

int readTemperatureSensorInCelsius() {
	uint16_t adcValue;
	float adcMilliVolts;
	int16_t tempC;
	ADCSRA |= (1 << ADSC);     /* Set Analogue Digital Start Conversion (ADSC) bit in Analogue Digital Conversion Status Register A (ADCSRA)    */
	//single conversion mode
	loop_until_bit_is_clear(ADCSRA, ADSC);          /* wait until done - The ADSC bit will be set back to zero when the conversion is done*/
	
	// ADC is actually two registers - ADCL and ADCH holding least and most significant bits respectively
	// It holds a 10 bit value, which GCC allows us to access as an unsigned 16 bit value
	adcValue = ADC;    /* read ADC in  - THe ADC contains the analogue to digital converted value (scaled by AREF) */
	
	adcMilliVolts= adcValue * (V_IN/1024);

	// Temp conversion 1V=50C
	tempC = (adcMilliVolts - 500)/10;
	
	return tempC;
}

void sendRF24(float celsius) {
	  radio.write(&celsius, sizeof(celsius) );
}

int main(void) {
	// -------- Inits --------- //
	 initUSART();
	 printString("Hello World!\r\n");
	 
	double temperatureInCelsius;
	
	initADC0();
	radio.begin();	radio.openWritingPipe(pipe);
	// ------ Event loop ------ //
	while (1) {

		temperatureInCelsius=readTemperatureSensorInCelsius();
		sendRF24(temperatureInCelsius);
		
		_delay_ms(500);
		
	}
	/* End event loop */
	
	return (0);                            /* This line is never reached */
}






