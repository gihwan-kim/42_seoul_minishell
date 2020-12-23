/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:07:34 by sancho            #+#    #+#             */
/*   Updated: 2020/12/21 17:37:06 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** envv : name=value
** str	 : name
*/

int			check_unset(char *str, char *envv)
{
	int		i;

	i = 0;
	while (str[i] && envv[i] && (str[i] == envv[i]) && (envv[i] != '='))
		i++;
	if ((str[i] == '\0') && (envv[i] == '='))
		return (TRUE);
	return (FALSE);
}

/*
** envv	: name
** str	: name
*/

static int	check_unset_2(char *str, char *envv)
{
	int		i;

	i = 0;
	if (ft_strlen(str) != ft_strlen(envv))
		return (FALSE);
	while (str[i] && envv[i] && (str[i] == envv[i]))
		i++;
	if (i == (int)ft_strlen(str))
		return (TRUE);
	return (FALSE);
}

int			ft_unset(char *str, char ***envv)
{
	int	i;
	int	last;

	last = 0;
	while (((*envv)[last]) != NULL)
		last++;
	if (last < 1)
		return (ERROR);
	i = -1;
	while ((*envv)[++i] != NULL)
		if (check_unset(str, (*envv)[i]) || check_unset_2(str, (*envv)[i]))
		{
			free((*envv)[i]);
			(*envv)[i] = ft_strdup((*envv)[last - 1]);
			free((*envv)[last - 1]);
			(*envv)[last - 1] = NULL;
			return (SUCCESS);
		}
	return (SUCCESS);
}
