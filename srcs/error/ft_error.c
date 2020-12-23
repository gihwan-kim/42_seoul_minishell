/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:51:38 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/21 17:34:02 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/*
** just display comment and return ERROR(0)
*/

int		strerror_int(int errnum)
{
	ft_putendl_fd(strerror(errnum), STDERR_FILENO);
	return (ERROR);
}

t_list	*strerror_list(int errnum)
{
	ft_putendl_fd(strerror(errnum), STDERR_FILENO);
	return (ERROR);
}

int		command_error_int(char *comment)
{
	ft_putendl_fd(comment, STDERR_FILENO);
	return (ERROR);
}

t_list	*command_error_list(char *comment)
{
	ft_putendl_fd(comment, STDERR_FILENO);
	return (ERROR);
}

void	bash_error(int type, char **program)
{
	int	idx;

	idx = 0;
	if (type == BASH_ERR_NOF)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(program[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else if (type == BASH_ERR_NOL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(program[0], STDERR_FILENO);
		ft_putendl_fd(" not a valid identifier", STDERR_FILENO);
	}
	else if (type == ENOENT)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(program[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(program[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(ENOENT), STDERR_FILENO);
	}
}
