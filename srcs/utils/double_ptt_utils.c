/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_ptt_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 23:04:49 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/11/18 12:42:48 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_splitjoin(char **split1, char **split2)
{
	char	** ret;
	int		i1;
	int		i2;

	i1 = 0;
	while (split1[i1])
		i1++;
	i2 = 0;
	while (split2[i2])
		i2++;
	if (!(ret = ft_calloc(i2 + i1 + 1, sizeof(char*))))
		return (ret);
	i1 = -1;
	while (split1[++i1])
		ret[i1] = ft_strdup(split1[i1]);
	i2 = -1;
	while (split2[++i2])
		ret[i1 + i2] = ft_strdup(split2[i2]);
	return (ret);
}

// 이중 배열 free 함수
void	free_double_str(char **ptr)
{
	int idx;

	idx = 0;
	if (ptr)
	{
		while (ptr[idx])
			free(ptr[idx++]);
		free(ptr);
	}
}

int		double_str_len(char **str)
{
	int idx;

	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

// 기존 ptr 은 free 하고 추가된 ptr 이 리턴됨
char	**add_double_str(char **ptr, char *str)
{
	char	**ret;
	int		len;
	int		idx;

	len = double_str_len(ptr) + 2;
	if (!(ret = ft_calloc(len, sizeof(char*))))
		return (NULL);
	idx = 0;
	while (ptr[idx])
	{
		ret[idx] = ft_strdup(ptr[idx]);
		idx++;
	}
	ret[idx] = ft_strdup(str);
	free_double_str(ptr);
	return (ret);
}
