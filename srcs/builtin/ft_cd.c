/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:04:12 by sancho            #+#    #+#             */
/*   Updated: 2020/12/21 15:29:46 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The getcwd() function copies the absolute pathname of the current working-
** directory into the memory referenced by buf and returns a pointer to buf.
**		return (fail - NULL) (success - pointer)
*/

#include "builtin.h"

static char	*find_old_pwd(char **envv)
{
	int	idx;

	idx = -1;
	while (envv[++idx])
		if (check_env("PWD=", envv[idx]))
			return (envv[idx] + 4);
	return (NULL);
}

int			ft_cd(char *src, char **envv)
{
	int		ret;
	char	*buf;
	char	*chbuf;
	char	*old_pwd;

	ret = chdir(src);
	if (ret == 0)
	{
		if (!(buf = malloc(sizeof(char) * 1000)))
			return (ERROR);
		if (!(buf = getcwd(buf, 1000)))
			return (ERROR);
		chbuf = ft_strjoin("PWD=", buf);
		old_pwd = ft_strjoin("OLDPWD=", find_old_pwd(envv));
		ft_export(chbuf, &envv);
		ft_export(old_pwd, &envv);
		free(buf);
		free(chbuf);
		free(old_pwd);
	}
	else
		return (ERROR);
	return (SUCCESS);
}
