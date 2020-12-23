/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:15:09 by sancho            #+#    #+#             */
/*   Updated: 2020/12/21 17:24:42 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(char **envv)
{
	int	i;

	i = 0;
	while (envv[i])
	{
		write(STDOUT_FILENO, envv[i], ft_strlen(envv[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (SUCCESS);
}
