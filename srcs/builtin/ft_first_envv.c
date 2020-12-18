/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_envv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:24:20 by sancho            #+#    #+#             */
/*   Updated: 2020/12/18 15:55:47 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	**ft_first_envv(char **envv)
{
	char	**new;
	int		i;

	i = 0;
	while (envv[++i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (envv[++i])
		new[i] = ft_strdup(envv[i]);
	new[i] = NULL;
	return (new);
}
