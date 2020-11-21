#include "minishell.h"

void	print(void *content)
{
	t_cmd *something = (t_cmd*)content;
	char **temp;
	int	idx;

	idx = 0;
	temp = something->program;
	printf("|%p|\n", content);
	while (temp[idx])
	{
		printf("최종 :|%s|\n", temp[idx]);
		idx++;
	}
}

int main()
{
	char *line;
	t_list	*wow;

	line = NULL;
	get_next_line(&line);
	wow = ft_parsing(line);
	if (wow)
		ft_lstiter(wow->next, print);
	else
	{
		printf("memory freed\n");
	}
	free(line);
	while(1);
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
