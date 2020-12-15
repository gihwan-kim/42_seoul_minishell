#include "parsing.h"
#include "error.h"

void *parsing_error(t_info *ptr1, t_list *ptr2, char *comment)
{
	if (ptr1)
	{
		if (ptr1->buff)
		{
			free(ptr1->buff);
			ptr1->buff = NULL;
		}
		// 이중 프리 방지 이후 lst clear 에서
		if (ptr1->quote == 0)
		{
			if (ptr1->content)
			{
				if (ptr1->content->program)
				{
					free_double_str(ptr1->content->program);
					ptr1->content->program = NULL;
				}
				free(ptr1->content);
				ptr1->content = NULL;
			}
		}
	}
	if (ptr2)
	{
		ft_lstclear(&(ptr2->next), free_program);
		free(ptr2);
	}
	ft_putstr_fd(comment, 1);
	return (NULL);
}

// void	free_program(void *content)
// {
// 	t_cmd *command;

// 	command = (t_cmd*)content;
// 	if (command)
// 	{
// 		free_double_str(command->program);
// 		free(command);
// 	}

// }

// int parsing_error(char *ptr1, t_list *ptr2, char *comment)
// {
// 	if (ptr1)
// 		free(ptr1);
// 	if (ptr2)
// 	{
// 		ft_lstclear(&(ptr2->next), free_program);
// 		free(ptr2);
// 	}
//     ft_putstr_fd(comment, 1);
// 	return (0);
// }
