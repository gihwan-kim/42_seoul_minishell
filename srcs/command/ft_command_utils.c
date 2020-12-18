/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 00:48:30 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/18 21:40:09 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

/*
** Returns the Nth content(program) of list
** N = count
*/

char	**get_cur_program(int count, t_list *cur_node)
{
	t_cmd	*cmd;
	int		i;

	i = 1;
	while (i < count)
	{
		cur_node = cur_node->next;
		i++;
	}
	if (cur_node)
		cmd = (t_cmd*)(cur_node->content);
	else
		return (NULL);
	return (cmd->program);
}

/*
** Returns the Nth node's next pointer value
** N = count
*/

t_list	*get_next_node(int count, t_list *cur_node)
{
	int		idx;

	idx = 0;
	while (idx < count && cur_node)
	{
		cur_node = cur_node->next;
		idx++;
	}
	return (cur_node);
}
