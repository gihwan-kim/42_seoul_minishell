/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:50:41 by sancho            #+#    #+#             */
/*   Updated: 2020/11/16 10:56:18 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

#include <stdio.h>

char
	*path_pro(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (s1_len + s2_len + 2))))
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '/';
	i++;
	while (i < (s1_len + s2_len + 1))
	{
		str[i] = s2[i - 1 - s1_len];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int
	path_run(char **info, char **path, char **envv)
{
	int		ret;
	int		i;
	char	*program;
	char	*origin;

	ret = 123;
	i = -1;
	while (path[++i])
	{
		origin = info[0];
		info[0] = path_pro(path[i], info[0]);
		//printf("%s\n", info[0]);
		ret = execve(info[0], info, envv);
		free(info[0]);
		info[0] = origin;
		free(path[i]);
	}
	return (ret);
}

int
	path_execve(char **info, char **envv)
{
	int		i;
	char	**path;
	char	*temp;
	int		result;

	i = -1;
	while (envv[++i])
		if (ft_strnstr(envv[i], "PATH", 4))
		{
			temp = ft_substr(envv[i], 5, ft_strlen(envv[i]));
			path = ft_split(temp, ':');
			free(temp);
			break ;
		}
	result = path_run(info, path, envv);
	write(0, "program not found!\n", 19);
	return (result);
}

int
	main(int argc, char **argv, char **envv)
{
	char	*info[] = {"host", "-a", NULL};

	path_execve(info, envv);
	return (0);
}
