/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:18:01 by sancho            #+#    #+#             */
/*   Updated: 2020/02/29 02:52:28 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	i;

	str1 = (char *)src;
	str2 = (char *)dst;
	i = 0;
	while (i < n)
	{
		str2[i] = str1[i];
		if (str1[i] == (char)c || str2[i] == (char)c)
		{
			return (dst + (++i));
		}
		i++;
	}
	return (NULL);
}
