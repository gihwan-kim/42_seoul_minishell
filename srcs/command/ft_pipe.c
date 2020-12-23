/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:07:03 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/21 13:48:36 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

/*
** flag rule
** ; | > >> <
** 0 1 2 3  4
*/

extern int	g_exit_status;
extern char	**g_envp;

int			count_pipe_element(t_list *list)
{
	t_cmd	*cmd;
	int		num;

	num = 1;
	while (list)
	{
		cmd = (t_cmd *)(list->content);
		list = list->next;
		if (cmd->flag == 1 && list)
			num++;
		else
			break ;
	}
	return (num);
}

int			init_pipe_fd(int pipe_element_num, int ***pipe_fd)
{
	int idx;

	idx = -1;
	if (!((*pipe_fd) = (int**)ft_calloc(pipe_element_num, sizeof(int*))))
		return (strerror_int(errno));
	while (++idx < pipe_element_num - 1)
	{
		if (!((*pipe_fd)[idx] = malloc(sizeof(int) * 2)))
			return (strerror_int(errno));
		if (pipe((*pipe_fd)[idx]) == -1)
			return (strerror_int(errno));
	}
	(*pipe_fd)[idx] = NULL;
	return (SUCCESS);
}

int			init_sub_shell_arr(int pipe_element_num,
								pid_t **sub_shell_arr,
								pid_t *only_parent,
								int *idx)
{
	*only_parent = 1;
	if (!((*sub_shell_arr) = ft_calloc(pipe_element_num, sizeof(pid_t))))
		return (strerror_int(errno));
	(*idx) = -1;
	while (++(*idx) < pipe_element_num && *only_parent)
	{
		if ((*only_parent = fork()) == -1)
			return (strerror_int(errno));
		(*sub_shell_arr)[(*idx)] = *only_parent;
	}
	return (SUCCESS);
}

/*
** 	write	read	pip_fd
** 	1		2		0
** 	2		3		1
** 	3		4		2
** 	...		...		...
*/

static void	wait_process(int idx, int pipe_elem_num,
						pid_t *sub_shell_arr, t_list *cur_node)
{
	t_cmd	*cmd;

	cmd = (t_cmd*)(get_next_node(idx, cur_node)->content);
	idx = -1;
	while (++idx < pipe_elem_num)
	{
		waitpid(sub_shell_arr[idx], &g_exit_status, 0);
		g_exit_status = g_exit_status / 256;
		if (g_exit_status)
			bash_error(g_exit_status, cmd->program);
	}
}

t_list		*ft_pipe(t_list *cur_node)
{
	pid_t	*sub_shell_arr;
	pid_t	only_parent;
	int		**pipe_fd;
	int		pipe_elem_num;
	int		idx;

	if ((pipe_elem_num = count_pipe_element(cur_node)) == 1)
		return (get_next_node(pipe_elem_num, cur_node));

	if (!init_pipe_fd(pipe_elem_num, &pipe_fd))
		return (get_next_node(pipe_elem_num, cur_node));
	if (!init_sub_shell_arr(pipe_elem_num, &sub_shell_arr, &only_parent, &idx))
		return (get_next_node(pipe_elem_num, cur_node));
	if (only_parent)
	{
		idx = -1;
		while (pipe_fd[++idx])
			close_pipe(pipe_fd[idx]);
		wait_process(idx, pipe_elem_num, sub_shell_arr, cur_node);
		return (get_next_node(pipe_elem_num, cur_node));
	}
	else
		execute_pipe(idx, pipe_fd, cur_node, pipe_elem_num);
	return (NULL);
}
