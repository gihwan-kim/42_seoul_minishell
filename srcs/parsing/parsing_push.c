#include "parsing.h"

int 	push_content(t_info *info, t_list *ret, char *str, int wow)
{
	if (wow == 3)
		info->i++;
	info->content->flag = wow;
	if (*(info->buff))
	{
		info->content->program[info->p_i] = ft_strdup((info->buff));
		info->content->program[info->p_i + 1] = NULL;
		(info->p_i)++;
		ft_bzero((info->buff), ft_strlen((info->buff)) + 1);
		info->j = 0;
	}
	if ((info->content->program)[0] == 0)
		return (ERRROR);
	else
	{
		ft_lstadd_back(&(ret), ft_lstnew((info->content)));
		if (info->i < ((int)ft_strlen(str) - 1 - check_next_is_space(str)))
		{
			(info->content) = ft_calloc(1, sizeof(t_cmd));
			(info->content)->program = ft_calloc(space_count(str) + 2, sizeof(char*));
		}
	}
	info->p_i = 0;
	return (SUCCESS);
}

void	push_buff(t_info *info)
{
	info->content->program[(info->p_i)] = ft_strdup(info->buff);
	info->content->program[(info->p_i) + 1] = NULL;
	(info->p_i)++;
	ft_bzero(info->buff, ft_strlen(info->buff) + 1);
	info->j = 0;
}
