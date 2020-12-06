/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 23:52:52 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/03 23:53:01 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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