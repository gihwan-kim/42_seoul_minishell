/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:48:46 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/18 21:49:57 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		space_count(char *str)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			count++;
		i++;
	}
	return (count);
}

int		check_next_is_space(char *str)
{
	int		index;
	int		count;

	index = ft_strlen(str) - 1;
	count = 0;
	while ((0 <= index) && (str[index] == ' '))
	{
		if (ft_strchr(";|><", str[index]))
			break ;
		count++;
		index--;
	}
	if (index <= 0)
		count = 0;
	return (count);
}

/*
** if ((info->content->program)[0] == 0 && info->content->flag <= 1)
** 	> hi echo wow	: error x,	(Ex. '>', '>>', '<' )
** 	| cmd			: error		(Ex. ';', '|')
*/

int		push_content(t_info *info, t_list *ret, char *str, int wow)
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
	if ((info->content->program)[0] == 0 && info->content->flag <= 1)
		return (ERROR);
	else
	{
		ft_lstadd_back(&(ret), ft_lstnew((info->content)));
		if (info->i < ((int)ft_strlen(str) - check_next_is_space(str) - 1))
		{
			(info->content) = ft_calloc(1, sizeof(t_cmd));
			(info->content)->program = ft_calloc(space_count(str) + 2,
													sizeof(char*));
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
