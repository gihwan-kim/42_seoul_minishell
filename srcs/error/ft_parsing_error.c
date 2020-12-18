/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:26:34 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/18 21:26:35 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "error.h"

static void	clear_ptr1(t_info *ptr1)
{
	if (ptr1->buff)
	{
		free(ptr1->buff);
		ptr1->buff = NULL;
	}
	if (ptr1->quote == 0)
	{
		if (ptr1->content)
		{
			if (ptr1->content->program)
			{
				free_double_str(ptr1->content->program);
				ptr1->content->program = NULL;
			}
			free(ptr1->content);
			ptr1->content = NULL;
		}
	}
}

void		*parsing_error(t_info *ptr1, t_list *ptr2, char *comment)
{
	if (ptr1)
		clear_ptr1(ptr1);
	if (ptr2)
	{
		ft_lstclear(&(ptr2->next), free_program);
		free(ptr2);
	}
	ft_putendl_fd(comment, STDERR_FILENO);
	return (NULL);
}
