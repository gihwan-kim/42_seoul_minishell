/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <gihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:58:00 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/11/26 16:23:32 by gihkim           ###   ########.fr       */
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
int check_unset(char *str, char *envv);

#endif
