/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:06:57 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/14 16:33:59 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

extern int g_exit_status;
extern char	**envp;

/*
	리다이렉션 백업 파일 
*/


// command > file
// command >> file
// command < file

// ">" 문자는 출력 리다이렉션(output redirection)을 위해 사용된다. 
// 그리고 출력된 파일은 존재하지 않을 경우 자동으로 생성되며, 
// 만약 이미 존재할 경우에는 기존 파일에 덮어쓰게(overwrite) 된다.

static int	execute_write(char **program, char *file, char *cmd, int mode)
{
	int		fd;
	int		check_cmd_type;
	int		stdout_copy;

	stdout_copy = dup(STDOUT_FILENO);
	// 쓰기 전용 | 존재할 경우 덮어쓰기 | 없으면 생성
	fd = open(file, mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (ERROR);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if ((check_cmd_type = check_command_is_builtin((const char*)cmd)))
	{
		execute_built_in(check_cmd_type, program);
		if (g_exit_status)
		{
			dup2(stdout_copy, STDOUT_FILENO);
			bash_error(g_exit_status, program);
			return (SUCCESS);
		}
	}
	else
		if (execute_external_cmd(program) == ERROR)
			return (ERROR);
	dup2(stdout_copy, STDOUT_FILENO);
	return (SUCCESS);
}


t_list	*ft_redirection_write(t_list *cur_node, int mode)
{
	t_list	*next_node;
	char	**cur_program;
	char	**next_program;
	char	**program;
	int		check;

	next_node = cur_node->next;
	cur_program = get_cur_program(1, cur_node);
	next_program = get_cur_program(1, next_node);
	check = SUCCESS;
	if (!next_node && !next_program[0])
		return (ERROR);								// 'cmd >'	or  '>' [bash: syntax error near unexpected token `newline']
	if (cur_program[0])								// cmd arg1 > file arg2 arg3 => final_porgarm : cmd arg1 arg2 arg3
	{
		program = ft_splitjoin(cur_program, next_program + 1);
		check = execute_write(program, next_program[0], cur_program[0], mode); // program file cmd
		free_double_str(program);
	}
	else if (next_program[1])						// > file cmd arg1 arg2 => final_program : cmd arg1 arg2
		check = execute_write(next_program + 1, next_program[0], next_program[1], mode);
	if (check == ERROR)
		strerror_list(errno);
	return (next_node);
}

t_list	*ft_redirection_overwirte(t_list *cur_node)
{
	return (ft_redirection_write(cur_node, O_CREAT | O_RDWR | O_TRUNC));
}

t_list	*ft_redirection_append(t_list *cur_node)
{
	return (ft_redirection_write(cur_node, O_CREAT | O_RDWR | O_APPEND));
}

static int	execute_read(char **program, char *file, char *cmd)
{
	int		fd;
	int		check_cmd_type;
	int		stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	fd = open(file, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);	// 읽기전용 | 소유자 읽기 허용 | 그룹 읽기 허용 | Other 읽기 허용
	if (fd < 0)
		return (ERROR);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if ((check_cmd_type = check_command_is_builtin((const char*)cmd)))
	{
		execute_built_in(check_cmd_type, program);
		if (g_exit_status)
		{
			dup2(stdin_copy, STDIN_FILENO);
			bash_error(g_exit_status, program);
			return (SUCCESS);
		}
	}
	else
		if (execute_external_cmd(program) == ERROR)
			return (ERROR);
	dup2(stdin_copy, STDIN_FILENO);
	return (SUCCESS);
}

t_list	*ft_redirection_read(t_list *cur_node)
{
	t_list	*next_node;
	char	**cur_program;
	char	**next_program;
	char	**program;
	int		check;
	
	next_node = cur_node->next;
	cur_program = get_cur_program(1, cur_node);
	next_program = get_cur_program(1, next_node);
	check = SUCCESS;
	if (!next_node && !next_program[0])
		return (ERROR);								// 'cmd >'	or  '>' [bash: syntax error near unexpected token `newline']
	if (cur_program[0])								// cmd arg1 > file arg2 arg3 => final_porgarm : cmd arg1 arg2 arg3
	{
		program = ft_splitjoin(cur_program, next_program + 1);
		check = execute_read(program, next_program[0], cur_program[0]); // program file cmd
		free_double_str(program);
	}
	else if (next_program[1])						// > file cmd arg1 arg2 => final_program : cmd arg1 arg2
		check = execute_read(next_program + 1, next_program[0], next_program[1]);
	if (check == ERROR)
		strerror_list(errno);
	return (next_node);
}
