/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:13:02 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/11/19 17:27:37 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

typedef struct s_cmd
{
	char		**arry; // cmd arg arg ...
	char		*flag;
	int			dollar;
}				t_cmd;

typedef struct s_index_info
{
	char		**cmd;
	int			idx;			// cmd[idx]
	int			flag;			// cmd[idx][flag] :  flag location index
	int			flag_is_double; // '>>' flag
	int			start;			// cmd[idx][start] : cmd[idx] 에서 flag 문자 이후에도 다른 명령어가 올 수있기 때문에 표시
}				t_info;

char	**parsing_cmd(char *cmd);
t_list	*parsing_set_cmd_list(char **cmd);
#endif