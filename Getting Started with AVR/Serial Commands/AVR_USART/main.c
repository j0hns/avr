#pragma GCC optimize ("O0") //Enable for simulator local variable debugging

#define F_CPU 8000000 // Clock Speed
#define BAUD 9600
#define UBRR_VALUE F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART_irq.h"
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE this_stdout = FDEV_SETUP_STREAM(USART_Transmit_IO, USART_Receive_IO,  _FDEV_SETUP_WRITE);

#define MAX_COMMAND_LENGTH 10
#define MAX_COMMAND_PARAMETERS 5
#define MAX_PARAMETER_LENGTH 10
char command[MAX_COMMAND_LENGTH];
char commandParameters[MAX_COMMAND_PARAMETERS][MAX_PARAMETER_LENGTH];
static int commandParametersIndex; //number of actual parameters in command
static int commandIndex=-1;

int	GetParmameter (int parameterIndex)
{
	return atoi(commandParameters[parameterIndex]);
}

void ExecuteCommand(void)
{
	printf("Executing Command: %s",command);
	for(int i=0;i<=commandParametersIndex;i++)
	{
		printf(",%s",commandParameters[i]);
	}
	printf(";");
	
	//execute command
	
	
	//reset
	 memset(command, 0, sizeof command);
	for (int i = 0; i < MAX_COMMAND_PARAMETERS; i++)for (int j = 0; j < MAX_COMMAND_LENGTH; j++){commandParameters[i][j] = '\0';}
	commandParametersIndex=-1;
	commandIndex=-1;
}

void HandleCommands(char c)
{
	//command handling loop

	const int MAXCOMMANDLENGTH=MAX_COMMAND_LENGTH;
	const int MAXCOMMANDPARAMETERS=MAX_COMMAND_PARAMETERS;
	const int MAXPARAMETERLENGTH=MAX_PARAMETER_LENGTH;
		if (c==';') //end of command
		{
			ExecuteCommand();
		}
		else
		{
			if(c==',')
			{
				commandIndex=MAXCOMMANDLENGTH+1; //indicate we are now processing parameters by setting commandIndex>MAX_COMMAND_LENGTH;
				commandParametersIndex++;
			}
			else
			{
				//keep processing command
				if (commandIndex<(MAXCOMMANDLENGTH-1))
				{
					command[++commandIndex]=c;
				}
				else
				{
					//process parameters
					if (commandParametersIndex>=0 && commandParametersIndex<MAXCOMMANDPARAMETERS)
					{
						int parameterLength=strlen(commandParameters[commandParametersIndex]);
						if (parameterLength<MAXPARAMETERLENGTH)
						{
							commandParameters[commandParametersIndex][parameterLength]=c;
						}
					}
				}
			}
		}
	
}



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








