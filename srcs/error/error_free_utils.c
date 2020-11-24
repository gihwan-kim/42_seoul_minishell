#include "error.h"

void	free_program(void *content)
{
	t_cmd *command;

	command = (t_cmd*)content;
	if (command)
	{
		// printf("ptr2 content %p\n", command);
		if (command->program)
		{
			// printf("content\n");
			free_double_str(command->program);
			// printf("content program freed\n");
			command->program = NULL;
		}
		free(command);
		// printf("content freed\n");;
	}
}
