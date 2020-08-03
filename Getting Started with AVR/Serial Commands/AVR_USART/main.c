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

typedef struct command {
	char	cmd[MAX_COMMAND_LENGTH];
	void	(*func)	(void);
};

void Cmd_Hello();
void Cmd_Bye();

command commands[] = {
	{"HELLO",	Cmd_Hello},
	{"BYE",		Cmd_Bye}
};

const int N_COMMANDS = sizeof (commands)/ sizeof (command);

void Cmd_Hello()
{
	for (int i=0;i<=CommandManager_GetParameterAsInteger(0);i++)
	{
		printf("Hello %s\n",i);
	}
}

void Cmd_Bye()
{
	for (int i=0;i<=CommandManager_GetParameterAsInteger(0);i++)
	{

		printf("BYE %s",i);
		for (int j=0;j<=CommandManager_GetParameterAsInteger(2);j++){printf("!");}
		puts("That's all")	;
	}
}

void CommandHandler()
{
	
	char* currentCommand=CommandManager_GetCommand();
	int commandParametersCount=CommandManager_GetParameterCount();
	
		printf("Executing Command: %s",currentCommand);
		for(int i=0;i<=commandParametersCount;i++)
		{
			printf(",%s",CommandManager_GetParameter(i));
		}
		printf(";");
		
		// Scan the command table looking for a match
		for (int cmd = 0; cmd < N_COMMANDS; cmd++) {
			if (strcmp (commands[cmd].cmd, currentCommand) == 0) {
				commands[cmd].func();  // command found, run its function
				goto done;
			}
		}
		
	done:
}
int main(void)
{
		//TEST
		char testCommand[]="simple;twoParams,123,456;threeparam,123.454,1234.87676,-1234213678678678674;5params,1,2,3,4,5;6params,1,2,3,4,5,6;done;";
		int endLoop=strlen(testCommand);
		for (int i=0;i < endLoop ;i++)
		{
			CommandManager_HandleCommands(testCommand[i],CommandHandler);
		}
		

	USART_Init(UBRR_VALUE); //Calculate baud rate
	sei(); //set up interrupt handling
	stdin=stdout=&this_stdout; //set up standard in & out
	
	printf("\nWaiting for command:");

	while(1)
	{
	
		
		while (!USART_ReceiveIsEmpty())
		{
			CommandManager_HandleCommands(USART_Receive());
		}
	}
		
	return 0;
}








