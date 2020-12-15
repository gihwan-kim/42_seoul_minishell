/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:07:03 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/15 12:44:40 by gihwan-kim       ###   ########.fr       */
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

static int		count_pipe_element(t_list *list)
{
	t_cmd *cmd;
	int num;

	num = 1;
	while (list)
	{
		cmd = (t_cmd *)(list->content);
		list = list->next;
		if (cmd->flag == 1 && list)
			num++;
		else
			break;
	}
	return (num);
}

static void		write_process(int idx, int *pipe_fd, t_list *cur_node)
{
	char		**cur_program;
	int			check_cmd_type;

	cur_program = get_cur_program(idx, cur_node);
	close(pipe_fd[0]);						// todo : error 처리
	if (pipe_fd[1] != STDOUT_FILENO)
	{
		close(1);
		dup2(pipe_fd[1], STDOUT_FILENO);				// todo : error 처리
		close(pipe_fd[1]);					// todo : error 처리
	}
	if ((check_cmd_type = check_command_is_builtin((const char*)cur_program[0])))
	{
		execute_built_in(check_cmd_type, cur_program);
		exit(g_exit_status);
	}
	else
		if(ft_execve(cur_program, g_envp) < 0)
			exit(BASH_ERR_NOF);
}

static void		read_and_write_process(int idx, int **pipe_fd, t_list *cur_node, int pipe_elem_num)
{
	char		**cur_program;
	int			check_cmd_type;

	cur_program = get_cur_program(idx, cur_node);
	close(pipe_fd[idx - 2][1]);
	if (pipe_fd[idx - 2][0] != STDIN_FILENO)
	{
		close(STDIN_FILENO);
		dup2(pipe_fd[idx - 2][0], STDIN_FILENO);
		close(pipe_fd[idx - 2][0]);
	}
	if (idx < pipe_elem_num)
	{
		close(pipe_fd[idx - 1][0]);						// todo : error 처리
		if (pipe_fd[idx - 1][1] != STDOUT_FILENO)
		{
			close(STDOUT_FILENO);
			dup2(pipe_fd[idx - 1][1], STDOUT_FILENO);				// todo : error 처리
			close(pipe_fd[idx - 1][1]);					// todo : error 처리
		}
	}
	if ((check_cmd_type = check_command_is_builtin((const char*)cur_program[0])))
	{
		execute_built_in(check_cmd_type, cur_program);
		exit(g_exit_status);
	}
	else
		if(ft_execve(cur_program, g_envp) < 0)
			exit(BASH_ERR_NOF);
}

// 명령어 수만큼 pipe 생성
int		init_pipe_fd(int pipe_element_num, int ***pipe_fd)
{
	int idx;

	idx = -1;
	if(!((*pipe_fd) = (int**)ft_calloc(pipe_element_num, sizeof(int*))))
		return (strerror_int(errno));
	while (++idx < pipe_element_num - 1)
    {
		if(!((*pipe_fd)[idx] = malloc(sizeof(int) * 2)))
			return (strerror_int(errno));
		if (pipe((*pipe_fd)[idx]) == -1)
			return (strerror_int(errno));
    }
	(*pipe_fd)[idx] = NULL;
	return (SUCCESS);
}

// 명령어 수만큼 프로세스 생성
int		init_sub_shell_arry(int pipe_element_num,
								pid_t **sub_shell_arry,
								pid_t *only_parent,
								int *idx)
{
	*only_parent = 1;
	if (!((*sub_shell_arry) = ft_calloc(pipe_element_num, sizeof(pid_t))))
		return (strerror_int(errno));
	(*idx) = -1;
	while (++(*idx) < pipe_element_num && *only_parent)			// parent process 에서만 fork 하기위해 only_parent 값 확인
	{
		if ((*only_parent = fork()) == -1)						// fork 실패시 에인
			return (strerror_int(errno));
		(*sub_shell_arry)[(*idx)] = *only_parent;
	}
	return (SUCCESS);
}

void	close_pipe(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

/*
** close_dont_use_pipe()
** 	This function closes pipe_fd which is not used in each child process
*/

void	close_dont_use_pipe(int idx, int **pipe_fd, int pipe_elem_num)
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

void	execute_pipe(int idx, int **pipe_fd, t_list *cur_node,
					int pipe_elem_num)
{
	close_dont_use_pipe(idx, pipe_fd, pipe_elem_num);
	if (idx == 1)
		write_process(idx, pipe_fd[0], cur_node);
	else
		read_and_write_process(idx, pipe_fd, cur_node, pipe_elem_num);
}

/*
** 	write	read	pip_fd
** 	1		2		0
** 	2		3		1
** 	3		4		2
** 	...		...		...
*/

t_list	*ft_pipe(t_list *cur_node)
{
	pid_t	*sub_shell_arry;
	pid_t	only_parent;
	int		**pipe_fd;
	int		pipe_elem_num;
	int		idx;

	if ((pipe_elem_num = count_pipe_element(cur_node)) == 1) 	// 원래는 " 명령어 | " 요거 밖에 없을 경우 입력을 더 받게 됨
		return (get_next_node(pipe_elem_num, cur_node));	   	// 어케할지 몰라서 일단 명령어 실행안하고 나오게함
	if (!init_pipe_fd(pipe_elem_num, &pipe_fd))
		return (get_next_node(pipe_elem_num, cur_node));
	if (!init_sub_shell_arry(pipe_elem_num, &sub_shell_arry, &only_parent, &idx))
		return (get_next_node(pipe_elem_num, cur_node));
	if (only_parent)
	{
		idx = -1;
		while (pipe_fd[++idx])
			close_pipe(pipe_fd[idx]);
		idx = -1;
		while (++idx < pipe_elem_num)
		{
			waitpid(sub_shell_arry[idx], &g_exit_status, 0);
			g_exit_status = g_exit_status / 256;
			if (g_exit_status) 							// ft_execve() 에서 해당되는 명령어 없을 경우
				bash_error(g_exit_status, ((t_cmd*)(get_next_node(idx, cur_node)->content))->program);
		}
		// 파이프는 마지막 명령어의 종료 상태 값을 받아옵니다.
		return (get_next_node(pipe_elem_num, cur_node));
	}
	else
		execute_pipe(idx, pipe_fd, cur_node, pipe_elem_num);
	return (NULL);
}
