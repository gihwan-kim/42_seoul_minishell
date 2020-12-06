/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <gihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:04:12 by sancho            #+#    #+#             */
/*   Updated: 2020/11/30 22:41:20 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		ft_cd(char *src, char **envv)
{
	int		ret;
	char	*buf;
	char	*chbuf;

	ret = chdir(src);
	if (ret == 0)
	{
		if (!(buf = malloc(sizeof(char) * 1000)))
			return (-1);
		buf = getcwd(buf, 1000);
		chbuf = ft_strjoin("PWD=", buf);
		ft_export(chbuf, &envv);
		free(buf);
		free(chbuf);
	}
	else
		write(0, "Error: Not Found Directory.\n", 28);
	return (ret);
}
