/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:03:40 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/23 19:41:18 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

extern int	g_exit_status;
extern char	**g_envp;

void	execute_built_in(int builtin_type, char **program)
{
	int	check;

	check = 0;
	if (builtin_type == 1)
		check = ft_echo(program);
	else if (builtin_type == 2)
		check = execute_ft_cd(program);
	else if (builtin_type == 3)
		check = ft_pwd();
	else if (builtin_type == 4)
		check = execute_ft_export(program);
	else if (builtin_type == 5)
		check = execute_ft_unset(program);
	else if (builtin_type == 6)
		check = ft_env(g_envp);
	else
	{
		// printf("g_ %d\n", g_exit_status);
		ft_exit(g_exit_status);
	}
	set_g_exit_status(check);
}

/*
** flag rule
** ; | > >> <
** 0 1 2 3  4
*/

t_list	*check_flag(t_list *cur_node)
{
	t_cmd *cmd;

	cmd = (t_cmd*)(cur_node->content);
	if (cmd->flag == 0)
		return (ft_semicolon(cur_node));
	else if (cmd->flag == 1)
		return (ft_pipe(cur_node));
	else if (cmd->flag == 2)
		return (redirection(cur_node));
	else if (cmd->flag == 3)
		return (redirection(cur_node));
	else if (cmd->flag == 4)
		return (redirection(cur_node));
	else
		return (cur_node);
}

/*
** controller()
** 	execute each node of t_list
**  1. second parsing
**	4. execute command
*/

void	controller(t_list *cmd_list)
{
	t_list	*cur_loc;
	t_cmd	*cmd;
	char	buf[1000];

	cur_loc = cmd_list->next;
	while (cur_loc)
	{
		cmd = (t_cmd*)(cur_loc->content);
		cmd->program = parsing_second(cmd->program, (const char **)g_envp);
		// ft_lstiter(cur_loc, print);
		// if (cmd->program[0] || cmd->flag >= 2)
			cur_loc = check_flag(cur_loc);
		// else
		// 	cur_loc = cur_loc->next;
		while (NULL == getcwd(buf, 1000))
			ft_cd("..", g_envp);
		errno = 0;
	}
	ft_lstclear(&(cmd_list->next), free_program);
}