#include "minishell.h"


/**
 * print_cmd_set
 * ft_lstiter 함수로 각 node 별로 함수를 적용시키면 될듯?
 *
 *
 */

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
	printf("\t명령 집합\n");
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
	ret = parsing_cmd(check);
	if (!ret)
		printf("error\n");
	printf("<<<파싱 결과>>>\n");
	while (ret[idx])
	{
		printf("%s\n", ret[idx]);
		idx++;
	}
	printf("\n\n");
	printf("<<<리스트에 명령어 담은 결과>>>\n");
	cmd_set_list = parsing_set_cmd_list(ret);
	// 각 명령집합별로 실행
	ft_lstiter(cmd_set_list, print_cmd_set);
}



// #include <stdio.h>

// int main(int argc, char **argv, char **envv)
// {
// 	char *pro[] = {"echo", "this","is" ,"test", "program", NULL};
// 	(void)argv;
// 	(void)argc;

// 	write(0, "0.----------------\n", 19);
// 	ft_first_envv(&envv);
// 	ft_export("ABC=SETABC", &envv);
// 	ft_export("ABC=CHANGEABC", &envv);
// 	ft_export("ABC=LASTCHANGE", &envv);
// 	ft_export("ABCD=OTHER", &envv);
// 	ft_export("TERM=TERM!!!!!!", &envv);
// 	ft_export("TERM=TERM@@@2222", &envv);
// 	ft_export("EEE=HELLO", &envv);
// 	ft_unset("ABCDF", &envv);
// 	ft_unset("ABC", &envv);
// 	ft_unset("USER", &envv);
// 	ft_export("FFF=FFF", &envv);
// 	ft_export("FFFF=FFFF", &envv);
// 	ft_unset("A", &envv);
// 	ft_unset("unsetdo not", &envv);
// 	ft_unset("FFF=", &envv);
// 	ft_env(envv);
// 	write(0, "1.----------------\n", 19);
// 	write(0, "pwd->\n", 6);
// 	ft_pwd();
// 	write(0, "cd srcs\n", 8);
// 	ft_cd("srcs", envv);
// 	ft_pwd();
// 	write(0, "cd ~\n", 5);
// 	ft_cd("~", envv);
// 	ft_pwd();
// 	write(0, "cd error\n", 9);
// 	ft_cd(".1./", envv);
// 	ft_pwd();
// 	write(0, "cd ../\n", 7);
// 	ft_cd("../", envv);
// 	ft_pwd();
// 	/*
// 	write(0, "env-----\n", 10);
// 	ft_env(envv);
// 	*/
// 	if(!fork())
// 		ft_execve(pro, envv);
// 	while(1);
// 	return 0;
// }
