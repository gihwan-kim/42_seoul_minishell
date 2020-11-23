#ifndef ERROR_H
# define ERROR_H

#include "minishell.h"
# define SYNTAX_ERROR "syntax error near unexpected token!\n"
# define QUOTE_ERROR "Quote number is odd!\n"
# define MEMORY_ERROR "Memory leak!\n"


int parsing_error(char *ptr1, t_list *ptr2, char *comment);
void	free_program(void *content);
#endif
