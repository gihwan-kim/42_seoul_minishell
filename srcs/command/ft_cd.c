/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:04:12 by sancho            #+#    #+#             */
/*   Updated: 2020/11/18 14:46:27 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

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
