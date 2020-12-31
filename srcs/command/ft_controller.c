/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:03:40 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/28 22:31:07 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

extern int	g_exit_status;
extern char	**g_envp;

void	exit_num(char **program)
{
	int	idx;

	idx = -1;
	if (program[1][0] == '-')
		idx = 0;
	while (program[1][++idx])
	{
		if (!ft_isdigit(program[1][idx]))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(program[0], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(program[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			ft_exit(255);
		}
	}
	ft_exit(ft_atoi(program[1]));
}

int		execute_ft_exit(char **program)
{
	int prg_len;

	prg_len = double_str_len(program);
	if (prg_len >= 3)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(program[0], STDERR_FILENO);
		ft_putstr_fd(": too many arguments", STDERR_FILENO);
		return (ERROR);
	}
	else if (prg_len == 2)
		exit_num(program);
	else
		ft_exit(g_exit_status);
	return (SUCCESS);
}

void	execute_built_in(int builtin_type, char **program)
{
	int	check;

	check = 0;
	if (builtin_type == 1)
		check = ft_echo(program);
	else if (builtin_type == 2)
		check = execute_ft_cd(program);
	else if (builtin_type == 3)
		check = ft_pwd();
	else if (builtin_type == 4)
		check = execute_ft_export(program);
	else if (builtin_type == 5)
		check = execute_ft_unset(program);
	else if (builtin_type == 6)
		check = ft_env(g_envp);
	else
		execute_ft_exit(program);
	set_g_exit_status(check);
}

/*
** flag rule
** ; | > >> <
** 0 1 2 3  4
*/

t_list	*check_flag(t_list *cur_node)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)(cur_node->content);
	if (cmd->flag == 0)
		return (ft_semicolon(cur_node));
	else if (cmd->flag == 1)
		return (ft_pipe(cur_node));
	else if (cmd->flag == 2)
		return (redirection(cur_node));
	else if (cmd->flag == 3)
		return (redirection(cur_node));
	else if (cmd->flag == 4)
		return (redirection(cur_node));
	else
		return (cur_node);
}

// pipe, redirection 의 경우 $ 일때 명ㄹ어어 하나씩 바꿔주는게 아니라
// 전부 바꿔주는 것 같다.
void	pipe_redir_parsing_second(t_list *node, t_cmd *prev_cmd)
{
	t_cmd	*cur_cmd;

	if (node->next == NULL)
		return ;
	node = node->next;
	cur_cmd = (t_cmd *)(node->content);
	while (node && prev_cmd->flag >= 1)
	{
		cur_cmd->program = parsing_second(cur_cmd->program,
											(const char **)g_envp);
		prev_cmd = cur_cmd;
		node = node->next;
	}
}

/*≠
** controller()
** 	execute each node of t_list
**  1. second parsing
**	4. execute command
*/

void	controller(t_list *cmd_list)
{
	t_list	*cur_loc;
	t_cmd	*cmd;
	char	buf[1000];

	cur_loc = cmd_list->next;
	while (cur_loc)
	{
		cmd = (t_cmd *)(cur_loc->content);
		cmd->program = parsing_second(cmd->program, (const char **)g_envp);
		pipe_redir_parsing_second(cur_loc, cmd);
		if (cmd->program[0] || cmd->flag >= 2)
			cur_loc = check_flag(cur_loc);
		else
			cur_loc = cur_loc->next;
		while (NULL == getcwd(buf, 1000))
			ft_cd("..", g_envp);
		errno = 0;
	}
	ft_lstclear(&(cmd_list->next), free_program);
}