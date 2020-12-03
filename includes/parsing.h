/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:13:02 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/03 23:52:32 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"
#include "command.h"


int		check_next_is_space(char *str);
int		space_count(char *str);
int		push_content(t_info *info, t_list *ret, char *str, int wow);
void	push_buff(t_info *info);
// t_list	*ft_parsing(char *str);
t_list	*parsing_first(char *str);
// char	*str_to_env(char *str, char **envv);

char	**parsing_second(char **program, const char **envp);
#endif
