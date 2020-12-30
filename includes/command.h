/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:43:24 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/28 22:11:43 by sancho           ###   ########.fr       */
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

/*
** ft_pipe_utils.c
*/
void	close_dont_use_pipe(int idx, int **pipe_fd, int pipe_elem_num);
void	execute_pipe(int idx, int **pipe_fd, t_list *cur_node,
					int pipe_elem_num);

/*
** ft_pipe_utils_2.c
*/

void	close_pipe(int *pipe_fd);

/*
** ft_execute_built_in.c
*/

int		check_name(char *name);
int 	execute_ft_cd(char **program);
int 	execute_ft_export(char **program);
void	set_g_exit_status(int check);
int		execute_ft_unset(char **program);

/*
** ft_controller.c
*/

t_list	*ft_pipe(t_list *cur_node);
t_list	*redirection(t_list *cur_node);
t_list	*ft_semicolon(t_list *cur_node);
void	controller(t_list *cmd_list);
void	close_pipe(int *pipe_fd);

typedef struct	s_redirection_info
{
	int			_stdin;
	int			_stdout;
	int			_copy_stdin;
	int			_copy_stdout;
}				t_rediret_info;

#endif