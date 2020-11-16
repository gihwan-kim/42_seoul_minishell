# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 01:47:11 by sancho            #+#    #+#              #
#    Updated: 2020/04/08 16:08:36 by sancho           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
RM	= rm -f
CFLAGS = -Wall -Wextra -Werror
HEADER = ./
SRCS	=	ft_memset.c\
ft_bzero.c\
ft_memcpy.c\
ft_memccpy.c\
ft_memmove.c\
ft_memchr.c\
ft_memcmp.c\
ft_strlen.c\
ft_strlcpy.c\
ft_strlcat.c\
ft_strchr.c\
ft_strrchr.c\
ft_strnstr.c\
ft_strncmp.c\
ft_atoi.c\
ft_isalpha.c\
ft_isdigit.c\
ft_isalnum.c\
ft_isascii.c\
ft_isprint.c\
ft_toupper.c\
ft_tolower.c\
ft_calloc.c\
ft_strdup.c\
ft_substr.c\
ft_strtrim.c\
ft_strjoin.c\
ft_split.c\
ft_itoa.c\
ft_strmapi.c\
ft_putchar_fd.c\
ft_putstr_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\

BONUSES	=	ft_lstnew.c\
ft_lstadd_front.c\
ft_lstsize.c\
ft_lstlast.c\
ft_lstadd_back.c\
ft_lstdelone.c\
ft_lstclear.c\
ft_lstiter.c\
ft_lstmap.c

OBJ = ${SRCS:.c=.o}
BOOBJ = ${BONUSES:.c=.o}

all: $(NAME)

.c.o :
	gcc -c $(CFLAGS) -I $(HEADER) $< -o $(<:.c=.o)

$(NAME) : ${OBJ}
		  ar rc $(NAME) $(OBJ)
clean:
	$(RM) ${OBJ} ${BOOBJ}

fclean: clean
		$(RM) $(NAME)

re : fclean all

bonus : all
		gcc -c $(CFLAGS) -I $(HEADER) $(BONUSES)
		ar rc $(NAME) $(BOOBJ) $(OBJ)

.PHONY : all bonus clean fclean re
