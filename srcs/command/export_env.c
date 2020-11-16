/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:07:34 by sancho            #+#    #+#             */
/*   Updated: 2020/11/16 23:31:10 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
환경변수 하나와 export할 함수를 비교하여 =앞의 값이 같은지 체크하여 참 거짓 반환
*/

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
/* export 시작*/

int	export_env(char *str, char ***envv)
{
	int		i;
	char	**new;

	i = 0;
	while ((*envv)[i] != NULL)
	{
		if (check_env(str, (*envv)[i]))
		{
			(*envv)[i] = ft_strdup(str);
			return (0);
		}
		i++;
	}
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (-1);
	i = -1;
	while ((*envv)[++i])
	{
		new[i] = ft_strdup((*envv)[i]);
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	*envv = new;
	return (0);
}
