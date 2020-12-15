#ifndef ERROR_H
# define ERROR_H

#include "minishell.h"
#include "parsing.h"
# define SYNTAX_ERROR "syntax error near unexpected token!"
# define QUOTE_ERROR "Quote number is odd!"
# define MEMORY_ERROR "Memory leak!"
# define PIPE_ERROR "Pipe function is failed!"
# define FORK_ERROR "Fork function is failed!"

void	*parsing_error(t_info *ptr1, t_list *ptr2, char *comment);
void	free_program(void *content);
int		strerror_int(int errnum);
t_list	*strerror_list(int errnum);
t_list  *command_error_list(char *comment);
int		command_error_int(char *comment);
void	bash_error(int type, char **program);
#endif
