/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:51:56 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/03 22:51:56 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"


void	free_program(void *content)
{
	t_cmd *command;

	command = (t_cmd*)content;
	if (command)
	{
		free_double_str(command->program);
		free(command);
	}

}

int parsing_error(char *ptr1, t_list *ptr2, char *comment)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
	{
		ft_lstclear(&(ptr2->next), free_program);
		free(ptr2);
	}
    ft_putstr_fd(comment, 1);
	return (0);
}
