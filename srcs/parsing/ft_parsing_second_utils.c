/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:09:00 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/18 21:48:17 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern int	g_exit_status;

/*
** j = set_env_to_buf(envp, find_env(prgm[0], &i), buf);
** if (quote != '\"')
** 	*idx = 1;
*/

void		check_split(int *j, int z, int *idx, char quote)
{
	*j = z;
	if (quote != '\"')
		*idx = 1;
}

void		init_word_parsing(char *quote, int *j, int *i)
{
	*i = -1;
	*quote = 0;
	*j = 0;
}

char		*find_env(char *str, int *i)
{
	char	*ret;
	int		start;
	int		idx;

	idx = *i + 1;
	start = *i + 1;
	while (str[idx])
		if (ft_isalnum(str[idx]) || str[idx] == '_')
			idx++;
		else
		{
			idx--;
			break ;
		}
	*i = idx;
	ret = ft_substr(str, start, idx - start + 1);
	return (ret);
}

int			set_env_to_buf(const char **envv, char *env, char *buf)
{
	int		i;

	i = -1;
	while (envv[++i])
	{
		if (check_unset(env, (char*)envv[i]))
		{
			ft_strlcat(buf,
						(char*)envv[i] + ft_strlen(env) + 1,
						ft_strlen(envv[i]) + ft_strlen(buf));
			break ;
		}
	}
	free(env);
	return ((int)ft_strlen(buf));
}

void		set_exit_status_to_buf(char *buf)
{
	char	*status;
	int		idx;

	idx = 0;
	status = ft_itoa(g_exit_status);
	ft_strlcat(buf, status, ft_strlen(buf) + ft_strlen(status) + 1);
}
