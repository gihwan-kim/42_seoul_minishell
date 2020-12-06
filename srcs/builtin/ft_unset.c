/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <gihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:07:34 by sancho            #+#    #+#             */
/*   Updated: 2020/11/30 22:41:57 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_unset(char *str, char *envv)
{
	int		i;

	i = 0;
	while (str[i] && envv[i] && (str[i] == envv[i]) && (envv[i] != '='))
		i++;
	if ((str[i] == '\0') && (envv[i] == '='))
		return (1);
	return (0);
}

int	ft_unset(char *str, char ***envv)
{
	int			i;
	int			last;

	last = 0;
	while (((*envv)[last]) != NULL)
		last++;
	if (last < 1)
		return (-1);
	i = -1;
	while ((*envv)[++i] != NULL)
		if (check_unset(str, (*envv)[i]))
		{
			free((*envv)[i]);
			(*envv)[i] = ft_strdup((*envv)[last - 1]);
			free((*envv)[last - 1]);
			(*envv)[last - 1] = NULL;
			return (0);
		}
	return (0);
}
