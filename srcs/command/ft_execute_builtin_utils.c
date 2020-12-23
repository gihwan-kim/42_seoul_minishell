/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_builtin_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:07:22 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/21 17:34:57 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

extern int	g_exit_status;
extern char	**g_envp;

int		check_name(char *name)
{
	int	idx;

	idx = -1;
	while (name[++idx])
		if (ft_isalnum(name[idx]) || name[idx] == '_')
			;
		else
			return (FALSE);
	if (!idx)
		return (FALSE);
	return (TRUE);
}

int		execute_ft_cd(char **program)
{
	int	idx;

	idx = -1;
	if (double_str_len(program) == 1)
	{
		while (g_envp[++idx])
		{
			if (check_env("HOME=", g_envp[idx]))
				return (ft_cd(g_envp[idx] + 5, g_envp));
		}
		return (ft_cd(g_envp[idx] + 5, g_envp));
	}
	else
		return (ft_cd(program[1], g_envp));
}

int		execute_ft_export(char **program)
{
	int idx;
	int check;

	idx = 0;
	check = 1;
	if (double_str_len(program) == 1)
		check = print_export(g_envp);
	else
	{
		while (program[++idx])
		{
			if (ft_export(program[idx], &g_envp))
				;
			else
				check = 0;
		}
	}
	if (check)
		return (1);
	else
		return (0);
}

int		execute_ft_unset(char **program)
{
	int	unset;
	int	idx;

	idx = 0;
	unset = 1;
	while (program[++idx])
	{
		if (check_name(program[idx]) && ft_unset(program[idx], &g_envp))
			;
		else
			unset = 0;
	}
	if (unset)
		return (1);
	else
		return (0);
}

/*
** BASH_ERR_EXE : permission, can't execute cmd
** BASH_ERR_NOF : no file, path
** BASH_ERR_NOL : normal error
*/

void	set_g_exit_status(int check)
{
	if (check == SUCCESS)
		g_exit_status = BASH_SUCCESS;
	else
	{
		if (errno == ESRCH || errno == ENXIO ||
			errno == ENOTDIR)
			g_exit_status = BASH_ERR_NOF;
		else if (errno == EACCES)
			g_exit_status = BASH_ERR_EXE;
		else
			g_exit_status = BASH_ERR_NOL;
	}
}
