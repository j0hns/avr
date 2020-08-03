#ifndef CommandManager_H_
#define CommandManager_H_

#define MAX_COMMAND_LENGTH 10
#define MAX_COMMAND_PARAMETERS 5
#define MAX_PARAMETER_LENGTH 10

int	GetParameter (int parameterIndex);
void HandleCommands(char c);

#endif 
