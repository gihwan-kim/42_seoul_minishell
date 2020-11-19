/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:58:00 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/11/19 16:58:27 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COMMAND_H
# define COMMAND_H

# include "minishell.h"

int	ft_first_envv(char ***envv);
int	ft_env(char **envv);
int	ft_execve(char **info, char **envv);
int	ft_export(char *str, char ***envv);
int	ft_unset(char *str, char ***envv);
int	ft_cd(char *src, char **envv);
int	ft_pwd(void);

#endif
