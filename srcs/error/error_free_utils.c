#include "error.h"

void	free_program(void *content)
{
	t_cmd *command;

	command = (t_cmd*)content;
	if (command)
	{
		free_double_str(command->program);
		free(command);
	}

}
