/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 21:30:37 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/28 23:07:50 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

extern int	g_exit_status;
extern char	**g_envp;

static void	write_process(int idx, int *pipe_fd, t_list *cur_node)
{
	char	**cur_prgm;
	int		check_cmd_type;

	cur_prgm = get_cur_program(idx, cur_node);
	close(pipe_fd[0]);
	if (pipe_fd[1] != STDOUT_FILENO)
	{
		close(1);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if ((check_cmd_type = check_command_is_builtin((const char *)cur_prgm[0])))
	{
		execute_built_in(check_cmd_type, cur_prgm);
		exit(g_exit_status / 256);
	}
	else if (ft_execve(cur_prgm, g_envp) < 0)
		exit(BASH_ERR_NOF);
}

/*
** pipe_fd[idx][0] : read
** pipe_fd[idx][1] : write
*/

static void	dup_pipe_std_stream(int **pipe_fd, int idx, int i, int j)
{
	if (i)
	{
		close(pipe_fd[idx][i]);
		if (pipe_fd[idx][j] != STDIN_FILENO)
		{
			close(STDIN_FILENO);
			dup2(pipe_fd[idx][j], STDIN_FILENO);
			close(pipe_fd[idx][j]);
		}
	}
	else
	{
		close(pipe_fd[idx][i]);
		if (pipe_fd[idx][j] != STDOUT_FILENO)
		{
			close(STDOUT_FILENO);
			dup2(pipe_fd[idx][j], STDOUT_FILENO);
			close(pipe_fd[idx][j]);
		}
	}
}

static void	read_and_write_process(int idx, int **pipe_fd,
									t_list *cur_node, int pipe_elem_num)
{
	char	**cur_prgm;
	int		check_cmd_type;

	cur_prgm = get_cur_program(idx, cur_node);
	dup_pipe_std_stream(pipe_fd, idx - 2, 1, 0);
	if (idx < pipe_elem_num)
		dup_pipe_std_stream(pipe_fd, idx - 1, 0, 1);
	if ((check_cmd_type = check_command_is_builtin((const char *)cur_prgm[0])))
	{
		execute_built_in(check_cmd_type, cur_prgm);
		exit(g_exit_status / 256);
	}
	else if (ft_execve(cur_prgm, g_envp) < 0)
		exit(BASH_ERR_NOF);
}

/*
** close_dont_use_pipe()
** 	This function closes pipe_fd which is not used in each child process
*/

void		close_dont_use_pipe(int idx, int **pipe_fd, int pipe_elem_num)
{
	int i;

	i = idx - 1;
	if (idx == 1)
		while (++i < pipe_elem_num - 1)
			close_pipe(pipe_fd[i]);
	else
	{
		while (++i < pipe_elem_num - 1)
			close_pipe(pipe_fd[i]);
		i = -1;
		while (++i < idx - 2)
			close_pipe(pipe_fd[i]);
	}
}

void		execute_pipe(int idx, int **pipe_fd, t_list *cur_node,
							int pipe_elem_num)
{
	close_dont_use_pipe(idx, pipe_fd, pipe_elem_num);
	if (idx == 1)
		write_process(idx, pipe_fd[0], cur_node);
	else
		read_and_write_process(idx, pipe_fd, cur_node, pipe_elem_num);
}
