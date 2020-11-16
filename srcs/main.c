#include "minishell.h"

#include <stdio.h>

int main(int argc, char **argv, char **envv)
{
	char *pro[] = {"lsa", "-al", NULL};
	(void)argv;
	(void)argc;

	//export_env("ABC=DSADSA", &envv);
	//export_env("ABC=11123SA", &envv);
	//export_env("ABCD=DSADSA", &envv);
	//export_env("TERM=DSADSA", &envv);
	env(envv);
	if(!fork())
		path_execve(pro, envv);
	while(1);
	return 0;
}
