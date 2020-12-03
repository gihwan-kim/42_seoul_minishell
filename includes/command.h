/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:43:24 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/03 22:43:25 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
#define COMMAND_H
#include "minishell.h"

int		check_command_is_builtin(const char *command);
t_list	*ft_pipe(t_list *cur_node);
t_list	*ft_redirection_overwirte();
t_list	*ft_redirection_wirte();
t_list	*ft_redirection_read();
t_list	*ft_redirection_insert();
t_list	*ft_semicolon();
void	controller(t_list *cmd_list);

#endif