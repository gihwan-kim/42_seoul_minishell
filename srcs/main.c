#include "minishell.h"

int main(int argc, char **argv, char **envv)
{
	char *pro[] = {"ls", "-al", NULL};
	(void)argv;
	(void)argc;
	env(envv);
	path_execve(pro, envv);

	return 0;
}
