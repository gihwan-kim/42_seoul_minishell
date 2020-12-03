#ifndef ERROR_H
# define ERROR_H

#include "minishell.h"
#include "parsing.h"
# define SYNTAX_ERROR "syntax error near unexpected token!\n"
# define QUOTE_ERROR "Quote number is odd!\n"
# define MEMORY_ERROR "Memory leak!\n"
# define PIPE_ERROR "Pipe function is failed!\n"
# define FORK_ERROR "Fork function is failed!\n"

void	*parsing_error(t_info *ptr1, t_list *ptr2, char *comment);
void	free_program(void *content);
t_list  *command_error_list(char *comment);
int		command_error_int(char *comment);
#endif
