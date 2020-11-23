#include "parsing.h"
#include "error.h"

void *parsing_error(t_info *ptr1, t_list *ptr2, char *comment)
{
	if (ptr1)
	{
		if (ptr1->buff)
			free(ptr1->buff);
		if (ptr1->content)
		{
			if (ptr1->content->program)
				free_double_str(ptr1->content->program);
			free(ptr1->content);
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
