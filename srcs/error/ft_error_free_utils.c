#include "error.h"

void	free_program(void *content)
{
	t_cmd *command;

	command = (t_cmd*)content;
	if (command)
	{
		if (command->program)
		{
			free_double_str(command->program);
			command->program = NULL;
		}
		free(command);
	}
}
