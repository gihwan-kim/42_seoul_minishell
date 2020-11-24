#ifndef ERROR_H
# define ERROR_H

#include "minishell.h"
# define SYNTAX_ERROR "syntax error near unexpected token!\n"
# define QUOTE_ERROR "Quote number is odd!\n"
# define MEMORY_ERROR "Memory leak!\n"

void	free_program(void *content);
#endif
