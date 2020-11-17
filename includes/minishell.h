#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include "../lib/libft/libft.h"
#include "command.h"
#include <unistd.h>
#include <signal.h>

int		get_next_line(char **line);

#endif
