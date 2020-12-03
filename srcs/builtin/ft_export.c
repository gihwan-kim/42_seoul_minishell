/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <gihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:07:34 by sancho            #+#    #+#             */
/*   Updated: 2020/11/30 22:41:38 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_env(char *str, char *envv)
{
	int		i;

	i = 0;
	while (str[i] && envv[i] && (str[i] == envv[i]) && (str[i] != '=')
		&& (envv[i] != '='))
		i++;
	if (i == 0)
		return (0);
	if ((envv[i] == '=') && (str[i] == '='))
		return (1);
	return (0);
}

int	ft_export(char *str, char ***envv)
{
	int			i;
	char		**new;

	i = -1;
	while ((*envv)[++i] != NULL)
		if (check_env(str, (*envv)[i]))
		{
			free((*envv)[i]);
			(*envv)[i] = ft_strdup(str);
			return (0);
		}
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (-1);
	i = -1;
	while ((*envv)[++i])
	{
		new[i] = ft_strdup((*envv)[i]);
		free((*envv)[i]);
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free(*envv);
	*envv = new;
	return (0);
}
