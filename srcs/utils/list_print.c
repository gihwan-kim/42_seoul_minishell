/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:40:23 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/03 22:41:48 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print(void *content)
{
	t_cmd   *something = (t_cmd*)content;
	char    **temp;
	int     idx;

	idx = 0;
	temp = something->program;
	printf("new node\n");
	while (temp[idx])
	{
		printf("최종 : |%s| flag |%d|\n", temp[idx], something->flag);
		idx++;
	}
}