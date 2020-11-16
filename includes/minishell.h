#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include "../lib/libft/libft.h"
#include <unistd.h>
#include <signal.h>

int		get_next_line(char **line);
int		path_execve(char **info, char **envv);
int		env(char **envv);
int		export_env(char *str, char ***envv);

#endif
