#pragma GCC optimize ("O0") //Enable for simulator local variable debugging

#define F_CPU 8000000 // Clock Speed
#define BAUD 9600
#define UBRR_VALUE F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "USART_irq.h"
#include "CommandManager.h"

static FILE this_stdout = FDEV_SETUP_STREAM(USART_Transmit_IO, USART_Receive_IO,  _FDEV_SETUP_WRITE);

int main(void)
{
		//TEST
		char testCommand[]="simple;twoParams,123,456;threeparam,123.454,1234.87676,-1234213678678678674;5params,1,2,3,4,5;6params,1,2,3,4,5,6;done;";
		int endLoop=strlen(testCommand);
		for (int i=0;i < endLoop ;i++)
		{
			HandleCommands(testCommand[i]);
		}
		

	USART_Init(UBRR_VALUE); //Calculate baud rate
	sei(); //set up interrupt handling
	stdin=stdout=&this_stdout; //set up standard in & out
	
	printf("\nWaiting for command:");

	while(1)
	{
	
		
		while (!USART_ReceiveIsEmpty())
		{
			HandleCommands(USART_Receive());
		}
	}
		
	return 0;
}








