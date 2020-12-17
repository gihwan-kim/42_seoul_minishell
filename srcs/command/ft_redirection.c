/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:06:57 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/17 12:02:33 by gihwan-kim       ###   ########.fr       */
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

char	**final_program(t_list *cur_node, char **cur_program)
{
	char	**tmp;
	char	**program;
	int		idx;

	idx = 1;
	if (cur_program)
		program = cur_program;
	else
		program = NULL;
	while ((cur_node = cur_node->next))
	{
		cur_program = ((t_cmd*)(cur_node->content))->program;
		tmp = program;
		program = ft_splitjoin(tmp, cur_program + 1);
		if (idx >= 2)
			free_double_str(tmp);
		idx++;
	}
	return (program);
}


char	**set_program(t_list *cur_node)
{
	char	**cur_program;

	cur_program = get_cur_program(1, cur_node);
	if (!(cur_node->next))
		return (NULL);								// 'cmd >'	or  '>'
	if (cur_program[0])								// cmd arg1 > file arg2 arg3 => final_porgarm : cmd arg1 arg2 arg3
		return (final_program(cur_node, cur_program));
	else											// > file cmd arg1 arg2 => final_program : cmd arg1 arg2
		return (final_program(cur_node, NULL));
}


int		file_open(int oflag, int mode, char *file)
{
	int		fd;

	fd = open(file, oflag, mode);
	if (fd < 0)
	{
		g_exit_status = 1;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		strerror_list(errno);
		errno = 0;
	}
	return (fd);
}

t_list	*execute_redirection(t_list *node, char **program, int fd, int flag)
{
	int		check_cmd_type;
	int		stream;
	int		stream_copy;

	if (flag == 4)
		stream = STDIN_FILENO;
	else
		stream = STDOUT_FILENO;
	stream_copy = dup(stream);
	dup2(fd, stream);
	close(fd);
	if ((check_cmd_type = check_command_is_builtin((const char*)program[0])))
	{
		execute_built_in(check_cmd_type, program);
		if (g_exit_status)
		{
			dup2(stream_copy, stream);
			bash_error(g_exit_status, program);
		}
	}
	else
		execute_external_cmd(program);
	dup2(stream_copy, stream);
	return (node);	
}

t_list	*recursive(t_list *node, char **program, int flag)
{
	t_cmd	*cur_cmd;
	int		mode;
	int		fd;

	mode = S_IRUSR | S_IRGRP | S_IROTH;
	cur_cmd = ((t_cmd*)(node->content));
	fd = 1;
	if (flag == 2)												// overwrite
		fd = file_open(O_CREAT | O_RDWR | O_TRUNC, S_IWUSR | mode, cur_cmd->program[0]);
	if (flag == 3)												// append
		fd = file_open(O_CREAT | O_RDWR | O_APPEND, S_IWUSR | mode, cur_cmd->program[0]);
	if (flag == 4)												// read
		fd = file_open(O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH, cur_cmd->program[0]);
	if (fd < 0)													// open 실패
		return (node);
	if (cur_cmd->flag <= 1 || node->next == NULL)				// 다음 명령어 없음 또는 리다이렉션이 아님
		return (execute_redirection(node, program, fd, flag));
	else														// > >> <
		return (recursive(node->next, program, cur_cmd->flag));	// 계속 반복하기
}

t_list	*redirection(t_list *cur_node)
{
	char	**program;
	t_cmd	*cur_cmd;
	t_list	*ret;

	program = set_program(cur_node);
	if (program == NULL)
	{
		command_error_list(SYNTAX_ERROR);
		return (cur_node->next);
	}
	cur_cmd = ((t_cmd*)(cur_node->content));
	ret = recursive(cur_node->next, program, cur_cmd->flag);
	if (g_exit_status && errno)
		strerror_list(errno);
	return (ret->next);
}
