/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_first.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:34:33 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/15 12:34:04 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*init(t_info *info, t_list **ret, char *str)
{
	info->p_i = 0;
	info->i = -1;
	info->quote = 0;
	info->j = 0;
	*ret = ft_lstnew(NULL);
	if (!(info->buff = ft_calloc(ft_strlen(str) + 1, sizeof(char))))
		return (parsing_error(info, NULL, MEMORY_ERROR));
	if (!(info->content = ft_calloc(1, sizeof(t_cmd))))
		return (parsing_error(info, NULL, MEMORY_ERROR));
	if (!(info->content->program = ft_calloc(space_count(str) + 2, sizeof(char*))))
		return (parsing_error(info, NULL, MEMORY_ERROR));
	return (info);
}

void	parsing_check(char *str, t_info *info, t_list *ret, int *flag_check)
{
	if (str[info->i] == info->quote)
	{
		info->quote = 0;
		info->buff[info->j++] = str[info->i]; // quote 문자도 담아주기
	}
	else if (info->quote == 0 && (str[info->i] == '\'' || str[info->i] == '\"'))
	{
		info->quote = str[info->i];
		info->buff[info->j++] = str[info->i];
	}
	else if (info->quote == 0 && str[info->i] == ';')
		*flag_check = push_content(info, ret, str, 0);
	else if (info->quote == 0 && str[info->i] == '|')
		*flag_check = push_content(info, ret, str, 1);
	else if (info->quote == 0 && str[info->i] == '>' && str[info->i + 1] != '>')
		*flag_check = push_content(info, ret, str, 2);
	else if (info->quote == 0 && str[info->i] == '>' && str[info->i + 1] == '>')
		*flag_check = push_content(info, ret, str, 3);
	else if (info->quote == 0 && str[info->i] == '<')
		*flag_check = push_content(info, ret, str, 4);
	else if (info->quote == 0 && str[info->i] == ' ')
	{
		if (*(info->buff))
			push_buff(info);
	}
	else if (info->quote != '\'' && str[info->i] == '\\')
	{	// single quote 가 아닌 경우에서 \ 문자를 만날 경우 뒷문자는 무조건 escpae 됨
		// double quote 안에서 \" 일 경우 " 도 그냥 문자로 처리해줌
		if (str[info->i + 1])
		{
			info->buff[info->j++] = str[info->i++];
			info->buff[info->j++] = str[info->i];
		}
	}
	else
		info->buff[info->j++] = str[info->i];
}

t_list	*parsing_first(char *str)
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