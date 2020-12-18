/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:04:22 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/18 19:55:15 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

extern int	g_exit_status;
extern char	**g_envp;

int		check_builtin(const char *cmd, const char *builtin, size_t cmd_len)
{
	size_t	idx;

	idx = 0;
	if (cmd_len != ft_strlen(builtin))
		return (FALSE);
	while (idx < cmd_len)
	{
		if ('A' <= cmd[idx] && cmd[idx] <= 'Z')
		{
			if ((cmd[idx] + 32 != builtin[idx]) && (cmd[idx] != builtin[idx]))
				return (FALSE);
		}
		else if ('a' <= cmd[idx] && cmd[idx] <= 'z')
		{
			if ((cmd[idx] - 32 != builtin[idx]) && (cmd[idx] != builtin[idx]))
				return (FALSE);
		}
		else
			return (FALSE);
		idx++;
	}
	return (TRUE);
}

int		check_command_is_builtin(const char *command)
{
	size_t	cmd_len;

	cmd_len = ft_strlen(command);
	if (check_builtin(command, "echo", cmd_len))
		return (1);
	else if (check_builtin(command, "cd", cmd_len))
		return (2);
	else if (check_builtin(command, "pwd", cmd_len))
		return (3);
	else if (check_builtin(command, "export", cmd_len))
		return (4);
	else if (check_builtin(command, "unset", cmd_len))
		return (5);
	else if (check_builtin(command, "env", cmd_len))
		return (6);
	else if (check_builtin(command, "exit", cmd_len))
		return (7);
	else
		return (0);
}
