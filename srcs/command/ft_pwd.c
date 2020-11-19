/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:39:04 by sancho            #+#    #+#             */
/*   Updated: 2020/11/18 13:51:54 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

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
