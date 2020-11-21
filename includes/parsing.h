/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:13:02 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/11/21 16:08:19 by sancho           ###   ########.fr       */
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

t_list *ft_parsing(char *str);
#endif
