NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_FLAGS = -lft -L./lib/libft
INC = -I./includes
RM = rm -rf


#SRCS = ./srcs/main.c

PARSING_SRCS = \
				ft_minisplit.c

COMMAND_SRCS = \
				ft_first_envv.c \
				ft_env.c \
				ft_execve.c \
				ft_export.c \
				ft_unset.c \
				ft_cd.c \
				ft_pwd.c

COMMAND_SRCS_DIR = ./srcs/command

PARSING_SRCS_DIR = ./srcs/parsing

UTILS_SRCS = \
			get_next_line.c

UTILS_SRCS_DIR = ./srcs/utils


# addprefix : 문자열 붙이기
SRCS_LIST = \
			$(addprefix $(PARSING_SRCS_DIR)/, $(PARSING_SRCS)) \
			$(addprefix $(UTILS_SRCS_DIR)/, $(UTILS_SRCS)) \
			$(addprefix $(COMMAND_SRCS_DIR)/, $(COMMAND_SRCS)) \
			./srcs/main.c
# .c -> .o
OBJS = $(SRCS:%.c=%.o)

# $(NAME) : $(OBJS)
# 	$(MAKE) -C lib/libft bonus
# 	gcc $(OBJS) -o $(NAME)


# .c.o :
# 	gcc -c $(CFLAGS) $< -o $(<:.c=.o)


all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C lib/libft bonus
	$(CC) $(CFLAGS) $(INC) $(SRCS_LIST) $(LIBFT_FLAGS) -o $(NAME)

clean :
	$(MAKE) -C lib/libft clean
	$(RM) $(OBJS)

fclean : clean
	$(MAKE) -C lib/libft fclean
	$(RM) $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re
