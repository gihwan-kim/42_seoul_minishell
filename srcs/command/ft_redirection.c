/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:06:57 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/28 23:56:58 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

extern int	g_exit_status;
extern char	**g_envp;
int			g_stream_backup = 0;

int			_stdin = -1;
int			_stdout = -1;
/*
** command > file	: overwrite or creat new file
** command >> file	: append
** command < file	: file's data is input of command
*/

// program 이 아무것도 없다면? > file arg > > > > :  에러 처리 !!! 12/26
char	**final_program(t_list *cur_node, char **cur_program)
{
	t_cmd	*cur_cmd;
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
		cur_cmd = (t_cmd*)(cur_node->content);
		cur_program = cur_cmd->program;
		if (cur_program[0] == 0)
			return (NULL);
		tmp = program;
		program = ft_splitjoin(tmp, cur_program + 1);
		if (idx >= 2)
			free_double_str(tmp);
		if (cur_cmd->flag < 2)
			break ; 
		idx++;
	}
	return (program);
}

int		file_open(int oflag, int mode, char *file, int flag)
{
	int		fd;
	int		stream;
	fd = open(file, oflag, mode);
	if (fd < 0)
	{
		g_exit_status = 256;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		strerror_list(errno);
		errno = 0;
		return (fd);
	}	
	if (flag == 4)
		stream = STDIN_FILENO;
	else
		stream = STDOUT_FILENO;
	dup2(fd, stream);
	return (stream);
}

t_list	*execute_redirection(t_list *node, char **program, int stream)
{
	int		check_cmd_type;

	if (program[0] == NULL)
		return (node);
	if ((check_cmd_type = check_command_is_builtin((const char*)program[0])))
	{
		execute_built_in(check_cmd_type, program);
		if (g_exit_status)
		{
			dup2(g_stream_backup, stream);
			if (g_exit_status && errno == 0)
				bash_error(g_exit_status / 256, program);
			else if (g_exit_status && errno == ENOENT)
				bash_error(ENOENT, program);
		}
	}
	else
	{
		if (execute_external_cmd(program) == ERROR)
			strerror_list(errno);
	}
	return (node);
}

/*
** flag = 2 : overwirte, trunc
** flag = 3 : append
** flag = 4 : read
** fd < 0 : open() failed
*/

t_list	*recursive(t_list *node, char **program, int flag, int fd)
{
	t_cmd	*cur_cmd;
	int		mode;

	mode = S_IRUSR | S_IRGRP | S_IROTH;
	cur_cmd = ((t_cmd*)(node->content));
	if (fd >= 1)
		close(fd);
	if (flag == 2)
		fd = file_open(O_CREAT | O_RDWR | O_TRUNC,
						S_IWUSR | mode, cur_cmd->program[0], flag);
	if (flag == 3)
		fd = file_open(O_CREAT | O_RDWR | O_APPEND,
						S_IWUSR | mode, cur_cmd->program[0], flag);
	if (flag == 4)
		fd = file_open(O_RDONLY ,S_IRUSR | S_IRGRP | S_IROTH,
						cur_cmd->program[0], flag);
	if (fd < 0)
		return (node);
	if (cur_cmd->flag >=2 && node->next != NULL)
		return (recursive(node->next, program, cur_cmd->flag, fd));
	if (cur_cmd->flag <= 1 || node->next == NULL)
		return (execute_redirection(node, program, fd));
	return (NULL);
}

/*
** program = NULL : 'cmd >'  or  '>'
**						=> syntax error
** cur_program[0] > 0 : 'cmd arg1 > file arg2 arg3'
**							=> final_porgarm : 'cmd arg1 arg2 arg3'
** cur_program[0] = 0 : '> file cmd arg1 arg2'
**							=> final_program : 'cmd arg1 arg2'
*/

t_list	*redirection(t_list *cur_node)
{
	char	**cur_program;
	char	**program;
	t_list	*ret;

	cur_program = get_cur_program(1, cur_node);
	_stdout = dup(STDOUT_FILENO);
	_stdin = dup(STDIN_FILENO);
	if (!(cur_node->next))
		program = NULL;
	if (cur_program[0])
		program = final_program(cur_node, cur_program);
	else
		program = final_program(cur_node, NULL);
	if (program == NULL || cur_node->next == NULL)
	{
		g_exit_status = 2 * 256;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		command_error_list(SYNTAX_ERROR);
		while (cur_node)
			cur_node = cur_node->next;
		return (cur_node);
	}
	ret = recursive(cur_node->next, program, ((t_cmd*)(cur_node->content))->flag, 0);
	if (_stdin >= 0)
		dup2(_stdin, STDIN_FILENO);
	if (_stdout >= 0)
		dup2(_stdout, STDOUT_FILENO);
	return (ret->next);
}
