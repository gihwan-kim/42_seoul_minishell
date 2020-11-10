CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = ./srcs/main.c
NAME = minishell

# .c -> .o
OBJS = $(SRCS:%c.=%.o)

$(NAME) : $(OBJS)
	# $(CC) $(CFLAGS) $(SRCS) -o $(NAME)

.c.o :
	gcc -c $(CFLAGS) $< -o $(<:.c=.o)

all : $(NAME)

clean : 
	rm -rf ./srcs/*.o

fclean :
	clean
	rm $(NAME)

re :
	fclean all

