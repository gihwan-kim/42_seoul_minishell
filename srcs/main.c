#include "minishell.h"

// int main(int argc, char **argv, char **envv)
// {
// 	char *pro[] = {"ls", "-al", NULL};
// 	(void)argv;
// 	(void)argc;
// 	env(envv);
// 	path_execve(pro, envv);

// 	return 0;
// }

void	print_cmd(void *content)
{
	t_cmd	*cmd;
	char	**tmp;
	int		idx;

	idx = 0;
	cmd =(t_cmd*)content;
	tmp = cmd->arry;
	while (tmp[idx])
	{
		printf("최종 |%s| flag :|%s|\n", tmp[idx], cmd->flag);
		idx++;
	}
}

void	print_cmd_set(void *content)
{
	// 각 명령어 별로 실행
	t_list *cmd_set;

	cmd_set = ((t_list*)(content))->next;
	ft_lstiter(cmd_set, print_cmd);
}

int main(int argc, char **argv)
{
	char 	**ret;
	char	*check;
	t_list	*cmd_set_list;
	int idx;
	(void)argc;
	(void)argv;
	idx = 0;

	get_next_line(&check);
	ret = ft_mininsplit(check);
	if (!ret)
		printf("error\n");
	printf("<<<파싱 결과>>>\n");
	while (ret[idx])
	{
		printf("%s\n", ret[idx]);
		idx++;
	}
	printf("<<<리스트에 명령어 담기>>>\n");
	cmd_set_list = get_cmd_list(ret);
	// 각 명령집합별로 실행
	ft_lstiter(cmd_set_list, print_cmd_set);
}