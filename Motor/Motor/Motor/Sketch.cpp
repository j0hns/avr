/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

//introduced code//
//#define F_CPU 8000000L

//#include <avr/io.h>
//#include <util/delay.h>
//end introduced code//


int speedPin = 3; //(PD3) H-bridge enable pin for speed control
int motor1APin = 2; //(PD2) H-bridge leg 1
int motor2APin = 4; //(PD4) H-bridge leg 2
int ledPin = 9; // (PB1) status LED
int speed_value_motor1=0; // value for motor speed
int increment=10;
void setup() {
	//introduced code//
	//DDRB |= (1 << PB0); //Data Direction Register B: Writing a one to the bit enables output.
	//end introduced code//
	
	// set digital i/o pins as outputs:
	pinMode(speedPin, OUTPUT);
	pinMode(motor1APin, OUTPUT);
	pinMode(motor2APin, OUTPUT);
	pinMode(ledPin, OUTPUT);
}

void loop() {
	
	//digitalWrite(ledPin, HIGH); // status LED is always on

	// put motor in forward motion
	digitalWrite(motor1APin, LOW); // set leg 1 of the H-bridge low
	digitalWrite(motor2APin, HIGH); // set leg 2 of the H-bridge high

	// just invert the above values for reverse motion,
	// i.e. motor1APin = HIGH and motor2APin = LOW

	// control the speed 0- 255
	speed_value_motor1 = speed_value_motor1 + increment; // half speed
	if (speed_value_motor1>255)
	{
		increment=-10;
		speed_value_motor1=255;
	}
	if (speed_value_motor1<0)
	{
		increment=10;
		speed_value_motor1=0;
	}
	
	analogWrite(ledPin, speed_value_motor1); // output speed as PWM value
	analogWrite(speedPin, speed_value_motor1); // output speed as PWM value

	delay(250);
}
