#include "command.h"

extern int g_exit_status;
extern char **envp;

void parsing_each_node(t_list *cur_node)
{
	t_cmd *cmd;

	cmd = (t_cmd*)(cur_node->content);

	cmd->program = parsing_second(cmd->program, (const char **)envp);
}

int		check_builtin(const char *command, const char *builtin, size_t cmd_len)
{
	size_t idx;

	idx = 0;
	if (cmd_len != ft_strlen(builtin))
		return (FALSE);
	while (idx < cmd_len)
	{
		if ('A' <= command[idx] && command[idx] <= 'Z')	
		{	// 대문자일 경우
			if (command[idx] + 32 != builtin[idx])
				return (FALSE);
		}
		else if ('a' <= command[idx] && command[idx] <= 'z')// 소문자일 경우
		{
			if (command[idx] - 32 != builtin[idx])
				return (FALSE);
		}
		else												// 알파벳이 아닌 경우
			return (FALSE);
		idx++;
	}
	return (TRUE);
}

int		check_command_is_builtin(const char *command)
{
	size_t	cmd_len;

	cmd_len = ft_strlen(command);
	if (check_builtin(command, "echo", cmd_len))
		return (1);
	else if (check_builtin(command, "cd", cmd_len))
		return (2);
	else if (check_builtin(command, "pwd", cmd_len))
		return (3);
	else if (check_builtin(command, "export", cmd_len))
		return (4);
	else if (check_builtin(command, "unset", cmd_len))
		return (5);
	else if (check_builtin(command, "env", cmd_len))
		return (6);
	else if (check_builtin(command, "exit", cmd_len))
		return (7);
	else
		return (0);	
}

/*
** flag rule
** ; | > >> <
** 0 1 2 3  4
*/

t_list	*check_flag(t_list *cur_node)
{
	t_cmd *cmd;

	cmd = (t_cmd*)(cur_node->content);
	if (cmd->flag == 0)
	{
		return (ft_semicolon());
	}
	else if (cmd->flag == 1)
	{
		return (ft_pipe(cur_node));
	}
	else if (cmd->flag == 2)
	{
		return (ft_redirection_overwirte());
	}
	else if (cmd->flag == 3)
	{
		return (ft_redirection_insert());
	}
	else if (cmd->flag == 4)
	{
		return (ft_redirection_read());
	}
	else
		return (NULL);
}



/*
** controller()
** 	execute each node of t_list
**  1. second parsing
**  2. check flag
**  3. check command
**	4. execute command
*/

void controller(t_list *cmd_list)
{
	t_list	*head;
	t_list	*cur_loc;
	printf("controller...\n");
	head = cmd_list;
	cur_loc = cmd_list->next;
	while (cur_loc)
	{
		parsing_each_node(cur_loc); // 1. second parsing
		printf("\n\n\nsecond parsing end\n");
		ft_lstiter(cur_loc, print);
		cur_loc = check_flag(cur_loc);
		cur_loc = cur_loc->next;
	}
}