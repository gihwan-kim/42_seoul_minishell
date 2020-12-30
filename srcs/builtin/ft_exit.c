/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 23:35:53 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/28 22:30:47 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_exit(int exit_status)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (exit_status >= 256)
		exit(exit_status / 256);
	else
		exit(exit_status);
}
