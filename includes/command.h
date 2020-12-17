/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:43:24 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/16 23:26:25 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
#define COMMAND_H
#include "minishell.h"

char	**get_cur_program(int idx, t_list *cur_node);
int		check_command_is_builtin(const char *command);
void	execute_built_in(int builtin_type, char **program);
int		execute_external_cmd(char **cur_program);
t_list	*get_next_node(int count, t_list *cur_node);

t_list	*ft_pipe(t_list *cur_node);
// t_list	*ft_redirection_overwirte(t_list *cur_node);
// t_list	*ft_redirection_append(t_list *cur_node);
// t_list	*ft_redirection_read(t_list *cur_node);

t_list	*redirection(t_list *cur_node);
t_list	*ft_semicolon(t_list *cur_node);
void	controller(t_list *cmd_list);

typedef struct	s_redirection_info
{
	int			oflag;
	int			mode;
	int			stream;
}				t_rediret_info;

// typedef struct	s_redirection_info
// {
// 	int			oflag;
// 	int			mode;
// 	int			stream;
// }				t_rediret_info;
#endif