NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS = ./srcs/main.c


# .c -> .o
OBJS = $(SRCS:%.c=%.o)

$(NAME) : $(OBJS)
	gcc $(OBJS) -o $(NAME)

.c.o :
	gcc -c $(CFLAGS) $< -o $(<:.c=.o)

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean 
	rm $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re

