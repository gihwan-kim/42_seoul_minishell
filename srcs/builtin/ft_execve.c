/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 01:17:44 by sancho            #+#    #+#             */
/*   Updated: 2020/12/21 17:20:42 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_status;

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
	char	*origin;
    struct stat sb;

	ret = 0;
	i = -1;
	if (path == NULL)
	{
		// PATH 환경 변수가 존재하지 않고, 인자(파일) 또한 존재하지 않을 경우
		// errno 가 2 로 설정되는데 이때 에러 문구 처리가 errno 문자열로 되어야함
		// 수정하기 12/22
		if (lstat(info[0], &sb) < 0)
			return (-1);
	}
	ret = execve(info[0], info, envv);
	while (path[++i])
	{
		origin = info[0];
		info[0] = path_pro(path[i], info[0]);
		ret = execve(info[0], info, envv);
		free(info[0]);
		info[0] = origin;
		free(path[i]);
	}
	return (ret);
}

/*
** if execve() function call is failed (no correct progarm)
** 	ft_execve() return -1
** if execve() function call is success
** 	no return value. process is changed to new process
*/

int
	ft_execve(char **info, char **envv)
{
	int		i;
	char	**path;
	char	*temp;
	int		result;

	path = NULL;
	i = -1;
	while (NULL != envv[++i])
		if (ft_strnstr(envv[i], "PATH=", 5))
		{
			temp = ft_substr(envv[i], 5, ft_strlen(envv[i]));
			path = ft_split(temp, ':');
			free(temp);
			break ;
		}
	result = path_run(info, path, envv);
	if (path != NULL)
		free(path);
	return (result);
}
