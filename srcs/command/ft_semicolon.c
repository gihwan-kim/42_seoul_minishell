/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_semicolon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 20:46:06 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/31 21:07:11 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

extern int	g_exit_status;
extern char	**g_envp;

int		execute_external_cmd(char **cur_program)
{
	pid_t	only_parent;
	int		child_status;

	if ((only_parent = fork()) == -1)
		return (ERROR);
	if (only_parent)
	{
		waitpid(only_parent, &child_status, 0);
		g_exit_status = child_status;
		if (g_exit_status)
			bash_error(g_exit_status / 256, cur_program);
	}
	else
	{
		if (ft_execve(cur_program, g_envp) < 0)
			exit(BASH_ERR_NOF);
	}
	return (SUCCESS);
}

t_list	*ft_semicolon(t_list *cur_node)
{
	char	**cur_prgm;
	int		check_cmd_type;

	cur_prgm = get_cur_program(1, cur_node);
	if ((check_cmd_type = check_command_is_builtin((const char*)cur_prgm[0])))
	{
		execute_built_in(check_cmd_type, cur_prgm);
		if (g_exit_status && errno == 0)
			bash_error(g_exit_status / 256,
						((t_cmd*)(cur_node->content))->program);
		else if (g_exit_status && errno == ENOENT)
			bash_error(ENOENT, ((t_cmd*)(cur_node->content))->program);
	}
	else
	{
		if (execute_external_cmd(cur_prgm) == ERROR)
			return (strerror_list(errno));
	}
	return (get_next_node(1, cur_node));
}
