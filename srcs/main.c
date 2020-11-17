#include "minishell.h"

#include <stdio.h>

int main(int argc, char **argv, char **envv)
{
	char *pro[] = {"echo", "this","is" ,"test", "program", NULL};
	(void)argv;
	(void)argc;

	ft_first_env(&envv);
	ft_export("ABC=SETABC", &envv);
	ft_export("ABC=CHANGEABC", &envv);
	ft_export("ABC=LASTCHANGE", &envv);
	ft_export("ABCD=OTHER", &envv);
	ft_export("TERM=TERM!!!!!!", &envv);
	ft_export("TERM=TERM@@@2222", &envv);
	ft_export("EEE=HELLO", &envv);
	ft_unset("ABCDF", &envv);
	ft_unset("ABC", &envv);
	ft_unset("USER", &envv);
	ft_export("FFF=FFF", &envv);
	ft_export("FFFF=FFFF", &envv);
	ft_unset("A", &envv);
	ft_unset("unsetdo not", &envv);
	ft_unset("FFF=", &envv);
	ft_env(envv);

	if(!fork())
		ft_execve(pro, envv);
	while(1);
	return 0;
}
