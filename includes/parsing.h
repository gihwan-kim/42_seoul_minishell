/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihkim <gihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:13:02 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/11/24 09:09:33 by gihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

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

t_list *ft_parsing(char *str);
void	*parsing_error(t_info *ptr1, t_list *ptr2, char *comment);
void	free_program(void *content);
#endif
