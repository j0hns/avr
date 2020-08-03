/*
 * CommandManager.c
 *
 * Created: 03/08/2020 23:07:29
 *  Author: John
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CommandManager.h"

static char command[MAX_COMMAND_LENGTH];
static char commandParameters[MAX_COMMAND_PARAMETERS][MAX_PARAMETER_LENGTH];
static int commandParametersIndex; //number of actual parameters in command
static int commandIndex=-1;

char *CommandManager_GetParameter(int parameterIndex)
{
	return commandParameters[parameterIndex];
}

int	CommandManager_GetParameterAsInteger (int parameterIndex)
{
	return atoi(commandParameters[parameterIndex]);
}

int	CommandManager_GetParameterCount ()
{
	return commandParametersIndex;
}

char *	CommandManager_GetCommand (void)
{
	return command;
}

void ExecuteCommand( void (*commandCallback)(void))
{

	
	//execute command
	(*commandCallback);
	
	//reset
	memset(command, 0, sizeof command);
	for (int i = 0; i < MAX_COMMAND_PARAMETERS; i++)for (int j = 0; j < MAX_COMMAND_LENGTH; j++){commandParameters[i][j] = '\0';}
	commandParametersIndex=-1;
	commandIndex=-1;
}

void CommandManager_HandleCommands(char c, void (*commandCallback)(void))
{
	//command handling loop

	const int MAXCOMMANDLENGTH=MAX_COMMAND_LENGTH;
	const int MAXCOMMANDPARAMETERS=MAX_COMMAND_PARAMETERS;
	const int MAXPARAMETERLENGTH=MAX_PARAMETER_LENGTH;
	if (c==';') //end of command
	{
		ExecuteCommand(commandCallback);
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
