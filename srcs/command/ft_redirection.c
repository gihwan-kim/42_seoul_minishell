/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:06:57 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/31 21:04:27 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

extern int	g_exit_status;
extern char	**g_envp;
int			g_stdin = -1;
int			g_stdout = -1;

/*
** command > file	: overwrite or creat new file
** command >> file	: append
** command < file	: file's data is input of command
*/

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

t_list	*execute_redirection(t_list *node, char **program)
{
	int		check_cmd_type;

	if (program[0] == NULL)
		return (node);
	if ((check_cmd_type = check_command_is_builtin((const char*)program[0])))
	{
		execute_built_in(check_cmd_type, program);
		if (g_exit_status)
		{
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
		fd = file_open(O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH,
						cur_cmd->program[0], flag);
	if (fd < 0)
		return (node);
	if (cur_cmd->flag >= 2 && node->next != NULL)
		return (recursive(node->next, program, cur_cmd->flag, fd));
	if (cur_cmd->flag <= 1 || node->next == NULL)
		return (execute_redirection(node, program));
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
	char	**program;
	t_list	*ret;

	g_stdout = dup(STDOUT_FILENO);
	g_stdin = dup(STDIN_FILENO);
	program = redir_set_program(cur_node, get_cur_program(1, cur_node));
	if (program == NULL || cur_node->next == NULL)
	{
		g_exit_status = 2 * 256;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		command_error_list(SYNTAX_ERROR);
		while (cur_node)
			cur_node = cur_node->next;
		return (cur_node);
	}
	ret = recursive(cur_node->next, program,
		((t_cmd*)(cur_node->content))->flag, 0);
	if (g_stdin >= 0)
		dup2(g_stdin, STDIN_FILENO);
	if (g_stdout >= 0)
		dup2(g_stdout, STDOUT_FILENO);
	return (ret->next);
}
