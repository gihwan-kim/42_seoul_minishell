#include "minishell.h"

<<<<<<< Updated upstream
void	print(void *content)
=======
/**
 * print_cmd_set
 * ft_lstiter 함수로 각 node 별로 함수를 적용시키면 될듯?
 *
 *
 */

void	print_cmd(void *content)
>>>>>>> Stashed changes
{
	t_cmd *something = (t_cmd*)content;
	char **temp;
	int	idx;

	idx = 0;
<<<<<<< Updated upstream
	temp = something->program;
	printf("|%p|\n", content);
	printf("최종 : content|%p|\n", temp);
	while (temp[idx])
=======
	cmd =(t_cmd*)content;
	tmp = cmd->arry;
	printf("!!\n");
	while (tmp[idx])
>>>>>>> Stashed changes
	{
		printf("최종 : |%s||%p| flag |%d|\n", temp[idx], temp[idx], something->flag);
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

	// wow 에서 확인 0 : 실패  >0 : 성공
	if (wow)
	{
		ft_lstiter(wow->next, print);
			t_list *tmp;

		tmp  = wow->next;
		while(tmp)
		{
			t_cmd	*tmp_c;

			tmp_c = (t_cmd*)(tmp->content);
			int idx =0;
			char **arry;
			arry = tmp_c->program;
			while (arry[idx])
			{
				free(arry[idx]);
				idx++;
			}
			free(arry);
			tmp = tmp->next;
		}
	}
<<<<<<< Updated upstream
	else
		printf("memory freed\n");


	free(line);
=======
	printf("\n\n");
	printf("<<<리스트에 명령어 담은 결과>>>\n");
	cmd_set_list = parsing_set_cmd_list(ret);
	// 각 명령집합별로 실행
	ft_lstiter(cmd_set_list, print_cmd_set);
>>>>>>> Stashed changes
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
