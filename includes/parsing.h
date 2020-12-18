/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:13:02 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/18 19:13:56 by gihwan-kim       ###   ########.fr       */
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
t_list	*parsing_first(char *str);

/*
** ft_parsing_second_utils.c
*/

void	check_split(int *j, int z, int *idx, char quote);
void	init_word_parsing(char *quote, int *j, int *i);
char	*find_env(char *str, int *i);
int		set_env_to_buf(const char **envv, char *env, char *buf);
void	set_exit_status_to_buf(char *buf);

char	**parsing_second(char **program, const char **envp);
#endif
