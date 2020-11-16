#include "minishell.h"

int main(int argc, char **argv, char **envv)
{
	char *pro[] = {"ls", "-al", NULL};
	(void)argv;
	(void)argc;
<<<<<<< Updated upstream
=======

	export_env("ABC=DSADSA", &envv);
	export_env("ABC=11123SA", &envv);
	export_env("ABCD=DSADSA", &envv);
	export_env("TERM=DSADSA", &envv);
>>>>>>> Stashed changes
	env(envv);
	path_execve(pro, envv);

	return 0;
}
