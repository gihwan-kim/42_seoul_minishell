/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:58:00 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/11 12:39:38 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
#define BUILTIN_H

#include "minishell.h"

// int	ft_first_envv(char ***envv);

char	**ft_first_envv(char **envv);

int	    check_env(char *str, char *envv);
int		ft_echo(char **program);
int		ft_env(char **envv);
int		ft_execve(char **info, char **envv);
int		ft_export(char *str, char ***envv);
int		ft_unset(char *str, char ***envv);
int		ft_cd(char *src, char **envv);
int		ft_pwd(void);
void	ft_exit(int exit_status);
int		check_unset(char *str, char *envv);
int 	print_export(char **envv);

#endif
