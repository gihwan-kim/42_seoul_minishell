#include "error.h"


void	free_program(void *content)
{
	t_cmd *command;

	command = (t_cmd*)content;
	printf("content : %p\n", content);
	if (command)
	{
		free_double_str(command->program);
		free(command);
	}

}

int parsing_error(char *ptr1, t_list *ptr2, char *comment)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
	{
		printf("list : %p %p\n", ptr2, ((t_cmd*)(ptr2->content))->program);
		printf("list : %p\n", ptr2->next);
		ft_lstclear(&(ptr2->next), free_program);
		free(ptr2);
	}
    ft_putstr_fd(comment, 1);
	return (0);
}
