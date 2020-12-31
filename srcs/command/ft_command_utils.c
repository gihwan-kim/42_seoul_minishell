/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 00:48:30 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/31 20:57:05 by sancho           ###   ########.fr       */
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

/*
** [ final_program() ]
** cmd > file arg1 arg2 > file
** 	=> final_program : cmd arg1 arg2
** > file cmd arg1 arg2 > file arg3
** 	=> final_program : cmd arg1 arg2 arg3
*/

char	**final_program(t_list *cur_node, char **cur_program)
{
	t_cmd	*cur_cmd;
	char	**tmp;
	char	**program;
	int		idx;

	idx = 1;
	if (cur_program)
		program = cur_program;
	else
		program = NULL;
	while ((cur_node = cur_node->next))
	{
		cur_cmd = (t_cmd*)(cur_node->content);
		cur_program = cur_cmd->program;
		if (cur_program[0] == 0)
			return (NULL);
		tmp = program;
		program = ft_splitjoin(tmp, cur_program + 1);
		if (idx >= 2)
			free_double_str(tmp);
		if (cur_cmd->flag < 2)
			break ;
		idx++;
	}
	return (program);
}

char	**redir_set_program(t_list *cur_node, char **cur_program)
{
	if (!(cur_node->next))
		return (NULL);
	if (cur_program[0])
		return (final_program(cur_node, cur_program));
	else
		return (final_program(cur_node, NULL));
}
