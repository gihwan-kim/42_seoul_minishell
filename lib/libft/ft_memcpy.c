/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:18:01 by sancho            #+#    #+#             */
/*   Updated: 2020/02/27 18:40:24 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *tmp;
	unsigned char *str;

	tmp = (unsigned char *)dest;
	str = (unsigned char *)src;
	if ((n == 0) || (dest == src))
		return (dest);
	while (n--)
		*tmp++ = *str++;
	return (dest);
}
