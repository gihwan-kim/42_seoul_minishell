/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:06:57 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/15 13:01:18 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

extern int g_exit_status;
extern char	**g_envp;

/*
** command > file	: overwrite or creat new file
** command >> file	: append
** command < file	: file's data is input of command
*/

static int		execute(char **program, char *file, char *cmd,
						t_rediret_info info)
{
	int		fd;
	int		check_cmd_type;
	int		stream_copy;

	stream_copy = dup(info.stream);
	fd = open(file, info.oflag, info.mode);
	if (fd < 0)
		return (ERROR);
	dup2(fd, info.stream);
	close(fd);
	if ((check_cmd_type = check_command_is_builtin((const char*)cmd)))
	{
		execute_built_in(check_cmd_type, program);
		if (g_exit_status)
		{
			dup2(stream_copy, info.stream);
			bash_error(g_exit_status, program);
			return (SUCCESS);
		}
	}
	else
		if (execute_external_cmd(program) == ERROR)
			return (ERROR);
	dup2(stream_copy, info.stream);
	return (SUCCESS);
}


static t_list	*ft_redirection(t_list *cur_node, t_list *next_node,
								t_rediret_info info)
{
	char	**cur_program;
	char	**next_program;
	char	**program;
	int		check;

	cur_program = get_cur_program(1, cur_node);
	next_program = get_cur_program(1, next_node);
	check = SUCCESS;
	if (!next_node)
	{
		command_error_list(SYNTAX_ERROR);
		return (cur_node);							// 'cmd >'	or  '>'
	}
	if (cur_program[0])								// cmd arg1 > file arg2 arg3 => final_porgarm : cmd arg1 arg2 arg3
	{
		program = ft_splitjoin(cur_program, next_program + 1);
		check = execute(program, next_program[0], cur_program[0], info); // program file cmd
		free_double_str(program);
	}
	else if (next_program[1])						// > file cmd arg1 arg2 => final_program : cmd arg1 arg2
		check = execute(next_program + 1, next_program[0], next_program[1], info);
	if (check == ERROR)								// 명령어 실패시 errno 가 설정되는 경우
		strerror_list(errno);						// 빌트인 명령어는 내부적으로 errno 있을 경우 출력해줌
	return (next_node);
}

t_list			*ft_redirection_overwirte(t_list *cur_node)
{
	t_rediret_info	info;

	info.oflag = O_CREAT | O_RDWR | O_TRUNC;
	info.mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	info.stream =  STDOUT_FILENO;
	return (ft_redirection(cur_node, cur_node->next, info));
}

t_list			*ft_redirection_append(t_list *cur_node)
{
	t_rediret_info	info;

	info.oflag = O_CREAT | O_RDWR | O_APPEND;
	info.mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	info.stream = STDOUT_FILENO; 
	return (ft_redirection(cur_node, cur_node->next, info));
}

t_list			*ft_redirection_read(t_list *cur_node)
{
	t_rediret_info	info;

	info.oflag = O_RDONLY;
	info.mode = S_IRUSR | S_IRGRP | S_IROTH;
	info.stream = STDIN_FILENO;
	return (ft_redirection(cur_node, cur_node->next, info));
}