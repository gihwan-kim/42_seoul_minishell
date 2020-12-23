/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 23:52:52 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/23 20:03:40 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_cmd
{
	char	**program;
	int		flag;
	int		redirection;
}				t_cmd;

typedef struct	s_parsing_info 
{
	int		p_i;
	int		i;
	int		j;
	char	quote;
	char	*buff;
	t_cmd	*content;
	t_list	*head;
}				t_info;
