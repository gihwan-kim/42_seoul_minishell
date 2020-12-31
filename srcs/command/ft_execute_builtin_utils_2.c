/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_builtin_utils_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 20:36:21 by sancho            #+#    #+#             */
/*   Updated: 2020/12/31 21:01:08 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

extern int	g_exit_status;

void	exit_num(char **program)
{
	int	idx;

	idx = -1;
	if (program[1][0] == '-')
		idx = 0;
	while (program[1][++idx])
	{
		if (!ft_isdigit(program[1][idx]))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(program[0], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(program[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			ft_exit(255);
		}
	}
	ft_exit(ft_atoi(program[1]));
}

int		execute_ft_exit(char **program)
{
	int prg_len;

	prg_len = double_str_len(program);
	if (prg_len >= 3)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(program[0], STDERR_FILENO);
		ft_putstr_fd(": too many arguments", STDERR_FILENO);
		return (ERROR);
	}
	else if (prg_len == 2)
		exit_num(program);
	else
		ft_exit(g_exit_status);
	return (SUCCESS);
}
