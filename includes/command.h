#ifndef COMMAND_H
# define COMMAND_H

#include "minishell.h"

int	ft_env(char **envv);
int	ft_execve(char **info, char **envv);
int	ft_export(char *str, char ***envv);

#endif
