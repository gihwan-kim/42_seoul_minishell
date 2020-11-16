/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:46:07 by sancho            #+#    #+#             */
/*   Updated: 2020/02/29 00:59:19 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dest, char *src, size_t size)
{
	unsigned int dest_size;
	unsigned int src_size;
	unsigned int result;

	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	result = src_size;
	if (size <= dest_size)
		result += size;
	else
		result += dest_size;
	src_size = 0;
	while (src[src_size] && dest_size + 1 < size)
		dest[dest_size++] = src[src_size++];
	dest[dest_size] = '\0';
	return (result);
}
