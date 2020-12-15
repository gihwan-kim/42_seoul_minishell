#include "minishell.h"


int		g_exit_status = 0;
char	**envp = NULL;

// int main(int argc, char **argv, char **envv)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)envv;
// 	char *line;
// 	// char *str;
// 	t_list	*wow;

// 	line = NULL;
// 	get_next_line(0, &line);
// 	// str = 	str_to_env(line, envv);
// 	// printf("str : |%s|\n", str);
// 	wow = parsing_first(line);
// 	printf("before free");
// 	// wow 에서 확인 0 : 실패  >0 : 성공
// 	if (wow)
// 	{
// 		ft_lstiter(wow->next, print);
// 			t_list *tmp;

// 		tmp  = wow->next;
// 		while(tmp)
// 		{
// 			t_cmd	*tmp_c;

// 			tmp_c = (t_cmd*)(tmp->content);
// 			int idx =0;
// 			char **arry;
// 			arry = tmp_c->program;
// 			while (arry[idx])
// 			{
// 				free(arry[idx]);
// 				idx++;
// 			}
// 			free(arry);
// 			tmp = tmp->next;
// 		}
// 	}
// 	else
// 		printf("memory freed\n");
// 	free(line);
// 	while(1);
// }



#include <stdio.h>

int main(int argc, char **argv, char **envv)
{
	char *pro[] = {"echo", "this","is" ,"test", "program", NULL};
	(void)argv;
	(void)argc;
	envp = ft_first_envv(envv);
	write(0, "0.----------------\n", 19);
	// ft_first_envv(&envp);
	ft_export("ABC=SETABC", &envp);
	ft_export("ABC=CHANGEABC", &envp);
	ft_export("ABC=LASTCHANGE", &envp);
	ft_export("ABCD=OTHER", &envp);
	ft_export("TERM=TERM!!!!!!", &envp);
	ft_export("TERM=TERM@@@2222", &envp);
	ft_export("EEE=HELLO", &envp);
	ft_unset("ABCDF", &envp);
	ft_unset("ABC", &envp);
	ft_unset("USER", &envp);
	ft_export("FFF=FFF", &envp);
	ft_export("FFFF=FFFF", &envp);
	ft_unset("A", &envp);
	ft_unset("unsetdo not", &envp);
	ft_unset("FFF=", &envp);
	printf("env\n\n");
	ft_env(envp);
	write(0, "1.----------------\n", 19);
	write(0, "pwd->\n", 6);
	ft_pwd();
	write(0, "cd srcs\n", 8);
	ft_cd("srcs", envp);
	write(0, "pwd->\n", 6);
	ft_pwd();
	write(0, "cd ~\n", 5);
	ft_cd("~", envp);
	write(0, "pwd->\n", 6);
	ft_pwd();
	write(0, "cd error\n", 9);
	ft_cd(".1./", envp);
	write(0, "pwd->\n", 6);
	ft_pwd();
	write(0, "cd ../\n", 7);
	ft_cd("../", envp);
	write(0, "pwd->\n", 6);
	ft_pwd();
	/*
	write(0, "env-----\n", 10);
	ft_env(envp);
	*/
	if(!fork())
		ft_execve(pro, envp);
	while(1);
	return 0;
}
