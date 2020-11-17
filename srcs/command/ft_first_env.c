/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:24:20 by sancho            #+#    #+#             */
/*   Updated: 2020/11/17 11:30:00 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	ft_first_env(char ***envv)
{
	int			i;
	char		**new;

	i = 0;
	while ((*envv)[++i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (-1);

	i = -1;
	while ((*envv)[++i])
		new[i] = ft_strdup((*envv)[i]);
	new[i] = NULL;
	*envv = new;
	return (0);
}
