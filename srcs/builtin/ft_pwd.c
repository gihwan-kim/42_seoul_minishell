/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:39:04 by sancho            #+#    #+#             */
/*   Updated: 2020/12/21 15:29:53 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** The getcwd() function copies the absolute pathname of the current working-
** directory into the memory referenced by buf and returns a pointer to buf.
**		return (fail - NULL) (success - pointer)
*/

int	ft_pwd(void)
{
	char	*buf;

	if (!(buf = malloc(sizeof(char) * 1000)))
		return (ERROR);
	if (!getcwd(buf, 1000))
		return (ERROR);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	return (SUCCESS);
}
