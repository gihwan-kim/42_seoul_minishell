/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:45:20 by sancho            #+#    #+#             */
/*   Updated: 2020/11/18 13:49:49 by sancho           ###   ########.fr       */
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
