#ifndef CommandManager_H_
#define CommandManager_H_

#define MAX_COMMAND_LENGTH 10
#define MAX_COMMAND_PARAMETERS 5
#define MAX_PARAMETER_LENGTH 10

char *	CommandManager_GetCommand (void);
char *CommandManager_GetParameter(int parameterIndex);
int	CommandManager_GetParameterAsInteger (int parameterIndex);
int	CommandManager_GetParameterCount ();
void CommandManager_HandleCommands(char c, void (*commandCallback)(void));

#endif 
