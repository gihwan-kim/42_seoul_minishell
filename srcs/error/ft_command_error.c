/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:51:38 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/04 00:49:24 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/*
** just display error stirng
*/

int		command_error_int(char *comment)
{
	ft_putstr_fd(comment, 1);
	return (ERROR);
}
t_list	*command_error_list(char *comment)
{
	ft_putstr_fd(comment, 1);
	return (ERROR);
}
