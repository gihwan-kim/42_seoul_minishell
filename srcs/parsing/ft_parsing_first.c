/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_first.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:34:33 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/23 20:04:09 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	*init(t_info *info, t_list **ret, char *str)
{
	info->p_i = 0;
	info->i = -1;
	info->quote = 0;
	info->j = 0;
	*ret = ft_lstnew(NULL);
	info->head = *ret;
	if (!(info->buff = ft_calloc(ft_strlen(str) + 1, sizeof(char))))
		return (parsing_error(info, NULL, MEMORY_ERROR));
	if (!(info->content = ft_calloc(1, sizeof(t_cmd))))
		return (parsing_error(info, NULL, MEMORY_ERROR));
	if (!(info->content->program = ft_calloc(space_count(str) + 2,
												sizeof(char*))))
		return (parsing_error(info, NULL, MEMORY_ERROR));
	return (info);
}

static void	set_quote(t_info *info, char quot, char buf_c)
{
	info->quote = quot;
	info->buff[info->j++] = buf_c;
}

static void	set_buff(t_info *info, char *str)
{
	info->buff[info->j++] = str[info->i++];
	info->buff[info->j++] = str[info->i];
}

void		parsing_check(char *str, t_info *inf, t_list *ret, int *flag_check)
{
	if (str[inf->i] == inf->quote)
		set_quote(inf, 0, str[inf->i]);
	else if (inf->quote == 0 && (str[inf->i] == '\'' || str[inf->i] == '\"'))
		set_quote(inf, str[inf->i], str[inf->i]);
	else if (inf->quote == 0 && str[inf->i] == ';')
		*flag_check = push_content(inf, ret, str, 0);
	else if (inf->quote == 0 && str[inf->i] == '|')
		*flag_check = push_content(inf, ret, str, 1);
	else if (inf->quote == 0 && str[inf->i] == '>' && str[inf->i + 1] != '>')
		*flag_check = push_content(inf, ret, str, 2);
	else if (inf->quote == 0 && str[inf->i] == '>' && str[inf->i + 1] == '>')
		*flag_check = push_content(inf, ret, str, 3);
	else if (inf->quote == 0 && str[inf->i] == '<')
		*flag_check = push_content(inf, ret, str, 4);
	else if (inf->quote == 0 && str[inf->i] == ' ')
	{
		if (*(inf->buff))
			push_buff(inf);
	}
	else if (inf->quote != '\'' && str[inf->i] == '\\' && str[inf->i + 1])
		set_buff(inf, str);
	else
		inf->buff[inf->j++] = str[inf->i];
}

t_list		*parsing_first(char *str)
{
	t_list	*ret;
	t_info	info;
	int		flag_check;

	if (!(init(&info, &ret, str)) && !(ret = NULL))
		return (NULL);
	flag_check = 1;
	while (str[++(info.i)])
	{
		parsing_check(str, &info, ret, &flag_check);
		if (!flag_check)
			return (parsing_error(&info, ret, SYNTAX_ERROR));
	}
	if (*(info.buff))
	{
		info.content->program[(info.p_i)] = ft_strdup(info.buff);
		info.content->program[(info.p_i) + 1] = NULL;
		info.p_i++;
	}
	if (info.p_i)
		ft_lstadd_back(&(ret), ft_lstnew(info.content));
	if (info.quote != 0)
		return (parsing_error(&info, ret, QUOTE_ERROR));
	free(info.buff);
	return (ret);
}
