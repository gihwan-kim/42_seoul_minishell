/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 03:17:35 by sancho            #+#    #+#             */
/*   Updated: 2020/02/29 03:04:59 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *last;

	last = 0;
	while (*s)
	{
		if (*s == c)
			last = (char*)s;
		s++;
	}
	if (last)
		return (last);
	if (c == '\0')
		return ((char*)s);
	return ((char*)0);
}
