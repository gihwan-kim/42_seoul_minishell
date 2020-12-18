/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 20:53:34 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/18 21:45:30 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** option_check()
** echo -nnnnn arg1			: n option (o)	=> 'arg1'
** echo -nnnnn -nnnn arg1	: n option (o)	=> 'arg1'
** echo -nmmm arg1			: n option (x)	=> '-nmmm arg1'
** echo -mmnn -nn arg1		: n option (x)	=> '-mmnn -nn arg1'
*/

static int	option_check(char **program, int *idx)
{
	int	i;
	int	ret;

	ret = 0;
	while (program[++(*idx)])
	{
		if (program[(*idx)][0] && program[(*idx)][1] &&
			(program[(*idx)][0] == '-') && program[(*idx)][1] == 'n')
		{
			i = 2;
			while (program[(*idx)][i])
			{
				if (program[(*idx)][i] != 'n')
				{
					ret = 0;
					break ;
				}
				ret = 1;
			}
		}
		else
			break ;
	}
	return (ret);
}

int			ft_echo(char **program)
{
	int idx;
	int	check;

	idx = 0;
	check = option_check(program, &idx);
	while (program[idx])
	{
		if (check)
			ft_putstr_fd(program[idx], 1);
		else
			ft_putendl_fd(program[idx], 1);
		idx++;
	}
	return (SUCCESS);
}
