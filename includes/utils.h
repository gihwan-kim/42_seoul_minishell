/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:18:52 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/11/19 16:58:55 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	UTILS_H
#define	UTILS_H
int		get_next_line(char **line);

// double str funtion
char	**ft_splitjoin(char **split1, char **split2);
void	free_double_str(char **ptr);
char	**add_double_str(char **ptr, char *str);
int		double_str_len(char **str);
#endif