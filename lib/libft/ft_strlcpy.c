/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:56:07 by sancho            #+#    #+#             */
/*   Updated: 2020/04/08 15:03:36 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t len;
	size_t index;

	len = 0;
	index = 0;
	while (src[len])
		++len;
	if (size == 0)
		return (len);
	while (src[index] != '\0' && index < (size - 1))
	{
		dest[index] = src[index];
		++index;
	}
	dest[index] = '\0';
	return (len);
}
