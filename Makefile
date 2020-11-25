NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_FLAGS = -lft -L./lib/libft
INC = -I./includes
RM = rm -rf

COMMAND_SRCS = \
				ft_first_envv.c \
				ft_env.c \
				ft_execve.c \
				ft_export.c \
				ft_unset.c \
				ft_cd.c \
				ft_pwd.c

COMMAND_SRCS_DIR = ./srcs/command

PARSING_SRCS = \
				parsing_error.c \
				parsing.c

PARSING_SRCS_DIR = ./srcs/parsing

UTILS_SRCS = \
			get_next_line.c \
			double_ptr_utils.c

UTILS_SRCS_DIR = ./srcs/utils

ERROR_SRCS = \
				error_free_utils.c

ERROR_SRCS_DIR = ./srcs/error

SRCS_LIST = \
			$(addprefix $(PARSING_SRCS_DIR)/, $(PARSING_SRCS)) \
			$(addprefix $(UTILS_SRCS_DIR)/, $(UTILS_SRCS)) \
			$(addprefix $(COMMAND_SRCS_DIR)/, $(COMMAND_SRCS)) \
			$(addprefix $(ERROR_SRCS_DIR)/, $(ERROR_SRCS)) \
			./srcs/main.c

OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS) $(SRCS_LIST)
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
