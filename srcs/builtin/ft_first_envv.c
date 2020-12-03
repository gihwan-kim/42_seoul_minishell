/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_envv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <gihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:24:20 by sancho            #+#    #+#             */
/*   Updated: 2020/11/30 22:41:49 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// int	ft_first_envv(char ***envv)
// {
// 	int			i;
// 	char		**new;

// 	i = 0;
// 	while ((*envv)[++i] != NULL)
// 		i++;
// 	if (!(new = malloc(sizeof(char*) * (i + 1))))
// 		return (-1);
// 	i = -1;
// 	while ((*envv)[++i])
// 		new[i] = ft_strdup((*envv)[i]);
// 	new[i] = NULL;
// 	*envv = new;
// 	return (0);
// }

char	**ft_first_envv(char **envv)
{
	int			i;
	char		**new;

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
