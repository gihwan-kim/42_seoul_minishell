/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 23:13:31 by sancho            #+#    #+#             */
/*   Updated: 2020/11/15 11:01:23 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_calloc(int size, int count)
{
	char	*new;
	int		len;
	int		i;

	len = size * count;
	new = (char*)malloc(len);
	i = 0;
	while (i < len)
		new[i++] = 0;
	return (new);
}

int		ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*ft_stradd(char *str, char c)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	new = ft_calloc(sizeof(char), len + 2);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	if (str)
		free(str);
	return (new);
}

char	*ft_substr(char *str, int begin, int len)
{
	char	*new;
	int		i;

	new = ft_calloc(sizeof(char), len + 1);
	i = 0;
	while (str[begin] && i < len)
		new[i++] = str[begin++];
	return (new);
}

int		get_next_line(char **line)
{
	static char	*s;
	char		*temp;
	char		buf[1];
	int			pos;

	if (!(line) || (!(s) && !(s = ft_calloc(sizeof(char), 1))))
		return (-1);
	while (read(0, buf, 1) > 0)
	{
		s = ft_stradd(s, buf[0]);
		if (buf[0] == '\n')
			break ;
	}
	if ((pos = ft_strchr(s, '\n')) >= 0)
	{
		*line = ft_substr(s, 0, pos);
		temp = s;
		s = ft_substr(s, pos + 1, ft_strchr(s, '\0'));
		free(temp);
		return (1);
	}
	*line = ft_substr(s, 0, ft_strchr(s, '\0'));
	free(s);
	return (0);
}
