/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:07:34 by sancho            #+#    #+#             */
/*   Updated: 2020/12/14 16:22:35 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// name, name= 인 경우 찾아줌
int	check_env(char *str, char *envv)
{
	int		i;

	i = 0;
	while (str[i] && envv[i] && (str[i] == envv[i]) && (str[i] != '=')
		&& (envv[i] != '='))
		i++;
	if (i == 0)
		return (0);
	if (((envv[i] == '=') && (str[i] == '=')) || ((envv[i] == '=') || str[i] == 0))
		return (1);
	return (0);
}

/*
** if program is only export string
** print envp
** Ex.
** export				: O -> print_export
** export name=value	: X -> ft_export
*/

int	print_export(char **envv)
{
	int	i;

	i = -1;
	while(envv[++i])
	{
		ft_putstr_fd(envv[i], 1);
		write(1, "\n", 1);
	}
	return (SUCCESS);
}

static char	**set_new_envv(char **new, char **old, char *str, int i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free(old);
	return (new);
}

/*
	export + something
		name=value
			목록에 name 있는지 없는지 확인
				o
					value 로 수정
				x
					새로 추가
		name= or name="" or name=''
			목록에 name 있는지 없는지 확인
				o
					값 바뀜
				x				
					value 가 NULL, 빈문자열로 새로 추가됨
		name
			목록에 name 있는지 없는지 확인
				o
					값 안바뀜
				x				
					value 가 NULL, 빈문자열로 새로 추가됨
	export + something
		envv 출력 -> echo 사용?
*/

int	ft_export(char *str, char ***envv)
{
	int			i;
	char		**new;

	i = -1;
	while ((*envv)[++i] != NULL)
		if (check_env(str, (*envv)[i]))
		{
			if (ft_strchr(str, '=')) // =value 또는 = 이 없고 name 만 있을 경우 아무일도 없도록
			{
				free((*envv)[i]);
				(*envv)[i] = ft_strdup(str);
			}
			return (SUCCESS);
		}
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (ERROR);
	i = -1;
	while ((*envv)[++i])
	{
		new[i] = ft_strdup((*envv)[i]);
		free((*envv)[i]);
	}
	new = set_new_envv(new, *envv, str, i);
	// new[i] = ft_strdup(str);
	// new[i + 1] = NULL;
	// free(*envv);
	// *envv = new;
	return (SUCCESS);
}
