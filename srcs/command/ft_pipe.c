/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:07:03 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/04 01:17:34 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
/*
** flag rule
** ; | > >> <
** 0 1 2 3  4
*/

extern int	g_exit_status;
extern char	**envp;

static int		count_pipe_element(t_list *list)
{
	t_cmd *cmd;
	int num;

	num = 1;
	while (list)
	{
		cmd = (t_cmd *)(list->content);
		if (cmd->flag == 1)
			num++;
		else
			break;
		list = list->next;
	}
	return (num);
}

static char		**get_cur_program(int idx, t_list *cur_node)
{
	t_cmd	*cmd;
	int		i;

	i = 1;
	while (i < idx)
	{
		cur_node = cur_node->next;
		i++;
	}
	cmd = (t_cmd*)(cur_node->content);
	return (cmd->program);
}

static void		write_process(int idx, int *pipe_fd, t_list *cur_node)
{
	const char	*cmd;
	char		**cur_program;
	int			check_cmd_type;

	cur_program = get_cur_program(idx, cur_node);
	cmd = (const char*)cur_program[0];
	close(pipe_fd[0]);						// todo : error 처리
	if (pipe_fd[1] != 1)
	{
		dup2(pipe_fd[1], 1);				// todo : error 처리
		close(pipe_fd[1]);					// todo : error 처리
	}
	check_cmd_type = check_command_is_builtin(cmd);
	if (check_cmd_type)
	{ /* TODO 12/4 : waitpid 및 프로세스의 리턴값에 대해 알아보고 보충하기 */
		exit(0);
	}
	else
		ft_execve(cur_program, envp);
}

static void		read_process(int idx, int *pipe_fd, t_list *cur_node)
{
	const char	*cmd;
	char		**cur_program;
	int			check_cmd_type;

	cur_program = get_cur_program(idx, cur_node);
	cmd = (const char*)cur_program[0];
	close(pipe_fd[1]);
	if (pipe_fd[0] != 0)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
	check_cmd_type = check_command_is_builtin(cmd);
	if (check_cmd_type)
	{ /* TODO 12/4 : waitpid 및 프로세스의 리턴값에 대해 알아보고 보충하기 */
		exit(100);
	}
	else
		ft_execve(cur_program, envp);
}

static t_list	*get_next_node(int pipe_element_num, t_list *cur_node)
{
	t_list	*ret;
	int		idx;

	idx = 0;
	while (idx < pipe_element_num)
	{
		ret = cur_node;
		cur_node = cur_node->next;
		idx++;
	}
	return (ret);
}


int		init_pipe_fd(int pipe_element_num, int ***pipe_fd)
{
	int idx;

	if(!((*pipe_fd) = ft_calloc(pipe_element_num, sizeof(int*))))
		return (command_error_int(MEMORY_ERROR));
	idx = -1;
	while (++idx < pipe_element_num)
    {
		if(!((*pipe_fd)[idx] = malloc(sizeof(int) * 2)))
			return (command_error_int(MEMORY_ERROR));
		if (pipe((*pipe_fd)[idx]) == -1)
			return (command_error_int(PIPE_ERROR));
    }
	return (SUCCESS);
}

int		init_sub_shell_arry(int pipe_element_num,
								pid_t **sub_shell_arry,
								pid_t *only_parent,
								int *idx)
{
	// element 별로 process 생성해주기
	if (!((*sub_shell_arry) = ft_calloc(pipe_element_num, sizeof(pid_t))))
		return (command_error_int(MEMORY_ERROR));
	(*idx) = -1;
	while (++(*idx) < pipe_element_num && *only_parent)			// parent process 에서만 fork 하기위해 only_parent 값 확인
	{
		if ((*only_parent = fork()) == -1)						// fork 실패시 에인
			return (command_error_int(FORK_ERROR));
		(*sub_shell_arry)[(*idx)] = *only_parent;
	}
	return (SUCCESS);
}

void	execute_pipe(int idx, int **pipe_fd, t_list *cur_node)
{
	if (idx == 1)
		write_process(idx, pipe_fd[0], cur_node);
	else
	{
		read_process(idx, pipe_fd[idx - 2], cur_node);
		write_process(idx, pipe_fd[idx - 1], cur_node);
	}	
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

	pipe_elem_num = count_pipe_element(cur_node);
	if (pipe_elem_num == 1) 									// 원래는 " 명령어 | " 요거 밖에 없을 경우 입력을 더 받게 됨
		return (get_next_node(pipe_elem_num, cur_node));	   	// 어케할지 몰라서 일단 명령어 실행안하고 나오게함
	only_parent = 1;
	if (!init_pipe_fd(pipe_elem_num, &pipe_fd) ||
		!init_sub_shell_arry(pipe_elem_num, &sub_shell_arry, &only_parent, &idx))
		return (ERROR);
	if (only_parent)
	{	/* TODO 12/4 : waitpid 및 프로세스의 리턴값에 대해 알아보고 보충하기 */
		waitpid(sub_shell_arry[pipe_elem_num - 1], &g_exit_status, 0);	// 파이프는 마지막 명령어의 종료 상태 값을 받아옵니다.
		return (get_next_node(pipe_elem_num, cur_node));
	}
	else
		execute_pipe(idx, pipe_fd, cur_node);
		// if (idx == 1)
		// 	write_process(idx, pipe_fd[0], cur_node);
		// else
		// {
		// 	read_process(idx, pipe_fd[idx - 2], cur_node);
		// 	write_process(idx, pipe_fd[idx - 1], cur_node);
		// }
	return (NULL);
}


// /bin/ls -al | /usr/bin/grep  hi.c | /bin/cat -e


// 나름 줄여보기 전 코드
	// if(!(pipe_fd = ft_calloc(pipe_element_num, sizeof(int*))))
	// 	return (command_error(MEMORY_ERROR));
	// idx = -1;
	// while (++idx < pipe_element_num)
    // {
	// 	if(!(pipe_fd[idx] = malloc(sizeof(int) * 2)))
	// 		return (command_error(MEMORY_ERROR));
	// 	if (pipe(pipe_fd[idx]) == -1)
	// 		return (command_error(PIPE_ERROR));
    // }
	// if (init_pipe_fd(pipe_element_num, &pipe_fd) == ERROR)
	// 	return (ERROR);

	// // element 별로 process 생성해주기
	// // if (!(sub_process_array = ft_calloc(pipe_element_num, sizeof(pid_t))))
	// // 	return (command_error(MEMORY_ERROR));
	// // idx = -1;
	// // while (++idx < pipe_element_num && only_parent)			// parent process 에서만 fork 하기위해 only_parent 값 확인
	// // {
	// // 	if ((only_parent = fork()) == -1)						// fork 실패시 에인
	// // 		return (command_error(FORK_ERROR));
	// // 	sub_process_array[idx] = only_parent;
	// // }
	// if (init_sub_process_array(pipe_element_num,
	// 							&sub_process_array, &only_parent, &idx) == ERROR)
	// 	return (ERROR);