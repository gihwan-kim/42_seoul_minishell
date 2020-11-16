/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:07:34 by sancho            #+#    #+#             */
/*   Updated: 2020/11/17 02:01:12 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

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
	static int	flag = 0;

	i = -1;
	while ((*envv)[++i] != NULL)
		if (check_env(str, (*envv)[i]))
		{
			(flag == 1) ? free((*envv)[i]) : (NULL);
			(*envv)[i] = ft_strdup(str);
			return (0);
		}
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (-1);
	i = -1;
	while ((*envv)[++i])
	{
		new[i] = ft_strdup((*envv)[i]);
		(flag == 1) ? free((*envv)[i]) : (NULL);
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	flag == 0 ? flag = 1 : free(*envv);
	*envv = new;
	return (0);
}