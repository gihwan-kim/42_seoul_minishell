/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <gihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:39:04 by sancho            #+#    #+#             */
/*   Updated: 2020/11/30 22:41:53 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_pwd(void)
{
	char	*buf;

	if (!(buf = malloc(sizeof(char) * 1000)))
		return (-1);
	getcwd(buf, 1000);
	write(0, buf, ft_strlen(buf));
	write(0, "\n", 1);
	free(buf);
	return (0);
}
