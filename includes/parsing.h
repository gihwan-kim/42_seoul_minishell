/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <gihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:13:02 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/11/26 16:24:21 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"
#include "command.h"

typedef struct	s_cmd
{
	char	**program;
	int		flag;

}				t_cmd;

typedef struct	s_parsing_info 
{
	int		p_i;
	int		i;
	int		j;
	char	quote;
	char	*buff;
	t_cmd	*content;
}				t_info;

int		check_next_is_space(char *str);
int		space_count(char *str);
int		push_content(t_info *info, t_list *ret, char *str, int wow);
void	push_buff(t_info *info);
void	*parsing_error(t_info *ptr1, t_list *ptr2, char *comment);
void	free_program(void *content);
t_list	*ft_parsing(char *str);
char	*str_to_env(char *str, char **envv);
#endif
