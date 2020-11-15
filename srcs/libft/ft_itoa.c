/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 20:03:50 by sancho            #+#    #+#             */
/*   Updated: 2020/04/08 16:56:27 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char		*num;
	long long	l;
	int			len;

	l = (long long)n;
	len = (l > 0) ? 0 : 1;
	l = (l > 0) ? l : l * -1;
	while (n)
		n = len++ ? n / 10 : n / 10;
	if (!(num = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	num[len] = '\0';
	while (l)
	{
		num[--len] = l % 10 + '0';
		l = l / 10;
	}
	if (len != 0 && num[1] == '\0')
		num[0] = '0';
	if (len != 0 && num[1] != '\0')
		num[0] = '-';
	return (num);
}
