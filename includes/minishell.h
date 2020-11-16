#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include "../lib/libft/libft.h"
#include <unistd.h>
#include <signal.h>

int		get_next_line(char **line);
int		path_execve(char **info, char **envv);
<<<<<<< Updated upstream
int		env(char **envv);
<<<<<<< HEAD
int		export_env(char *str, char ***envv);
=======

=======
int		ft_env(char **envv);
int		ft_export(char *str, char ***envv);
>>>>>>> Stashed changes
>>>>>>> main

#endif
