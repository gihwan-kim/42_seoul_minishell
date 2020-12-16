#include "command.h"

extern int g_exit_status;
extern char **g_envp;

void parsing_each_node(t_list *cur_node)
{
	t_cmd *cmd;

	cmd = (t_cmd*)(cur_node->content);
	cmd->program = parsing_second(cmd->program, (const char **)g_envp);
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
			if ((command[idx] + 32 != builtin[idx]) && (command[idx] != builtin[idx]))
				return (FALSE);
		}
		else if ('a' <= command[idx] && command[idx] <= 'z')	// 소문자일 경우
		{
			if ((command[idx] - 32 != builtin[idx]) && (command[idx] != builtin[idx]))
				return (FALSE);
		}
		else													// 알파벳이 아닌 경우
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

static int		check_name(char *name)
{
	int	idx;

	idx = -1;
	while (name[++idx])
		if (ft_isalnum(name[idx]) || name[idx] == '_')
			;
		else
			return (FALSE);
	return (TRUE);
}

/*
** int	execute_built_in(int builtin_type, char **program)
** 1. ft_[builtin command]() 함수를 호출해서 빌트인 명령어를 실행
**		SUCCESS (1) : 빌트인 명령어가 정상적으로 실행정
**		ERROR	(0): 빌트인 명령어가 정상적으로 실행되지 않음 
**			=>	errno 가 설정됨 execute_built_in() 호출 이후 
**				strrerr_[dataType](errno) 함수 호출해서 에러 문구 출력해줘야함
** 2. ft_[builtin command]() 함수의 리턴 값을 통해 g_exit_status 설정
*/

void	execute_built_in(int builtin_type, char **program)
{
	int	idx;
	int	check;
	int unset;

	idx = 0;
	check = 0;
	unset = 1;
	if (builtin_type == 1)
		check = ft_echo(program);
	else if (builtin_type == 2)
		if (double_str_len(program) == 1)
			check = ft_cd(program[0], g_envp);
		else
			check = ft_cd(program[1], g_envp);
	else if (builtin_type == 3)
		check = ft_pwd();
	else if (builtin_type == 4)
		if (double_str_len(program) == 1)
			check = print_export(g_envp);
		else
			while (program[++idx])
				check = ft_export(program[idx], &g_envp);
	else if (builtin_type == 5)
	{
		while (program[++idx])
			if (check_name(program[idx]))
				ft_unset(program[idx], &g_envp);
			else
				unset = 0;
		if (unset)
			check = 1;
	}
	else if (builtin_type == 6)
		check = ft_env(g_envp);
	else
		ft_exit(g_exit_status);
	// bash 의 eixt status 설정
	if (check == SUCCESS)
		g_exit_status = BASH_SUCCESS;
	else
		if (errno == ENOENT || errno == ESRCH || errno == ENXIO ||
			errno == ENOTDIR) 		// 파일이 존재하지 않음, path 문제
			g_exit_status = BASH_ERR_NOF;
		else if(errno == EACCES) 	// 명령을 실행할 수 없음, 권한 문제 또는 실행할 수 없는 경우
			g_exit_status = BASH_ERR_EXE;
		else						// 일반적인 에러
			g_exit_status = BASH_ERR_NOL;
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

	head = cmd_list;
	cur_loc = cmd_list->next;
	while (cur_loc)
	{
		parsing_each_node(cur_loc); // 1. second parsing
		cur_loc = check_flag(cur_loc);
		// ft_lstiter(cur_loc, print);
	}
	ft_lstclear(&(cmd_list->next), free_program);
	// 메모리 해제
}