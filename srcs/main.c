#include "minishell.h"

#include <stdio.h>

int main(int argc, char **argv, char **envv)
{
	char *pro[] = {"ls", "-al", NULL};
	(void)argv;
	(void)argc;

	ft_export("ABC=DSADSA", &envv);
	ft_export("ABC=11123SA", &envv);
	ft_export("ABCD=DSADSA", &envv);
	ft_export("TERM=DSADSA", &envv);
	ft_env(envv);

	if(!fork())
		ft_execve(pro, envv);
	while(1);
	return 0;
}
