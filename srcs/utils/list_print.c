/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:40:23 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/18 21:51:18 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print(void *content)
{
	t_cmd	*something;
	char	**temp;
	int		idx;

	something = (t_cmd*)content;
	idx = 0;
	temp = something->program;
	printf("new node\n");
	printf("flag |%d| %s\n", something->flag, temp[0]);
	while (temp[idx])
	{
		printf("arg : |%s| flag |%d|\n", temp[idx], something->flag);
		idx++;
	}
}
