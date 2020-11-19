/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:02:29 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/11/19 16:06:28 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 				[ flag ]
 * boudary_single : flag 가 문자 하나인 경우
 * 		mandatory	: >, <, |, ;
 * 		bonus		: >, <, |, ;
 *
 * boundary_doube : flag 가 문자 두개인경우
 * 		mandatory 	: >>
 * 		bonus		: ||, >>, <<, &&
 *
 * check_flag : boundary 문자 까지 인덱스 값을 리턴
 *
 * [명령 집합 목록]
 * 0 -> (명령 집합) : command 구조체 - command 구조체  : flag 있는 경우
 * 1 -> (명령 집합) : command 구조체					: falg 없는 경우
 */

int		check_flag(char *word, t_info *info)
{
	char	*flag_single;
	char	*flag_double;
	int		idx;

	flag_single = "<|;";
	flag_double = ">";
	info->flag_is_double = FALSE;
	idx = info->start - 1;
	while (word[++idx])
		if (ft_strchr(flag_single, word[idx]))
		{
			info->flag = idx;
			return (TRUE);
		}
		else if (ft_strchr(flag_double, word[idx]))
		{
			info->flag = idx;
			if (word[idx] == word[idx + 1])
				info->flag_is_double = TRUE;
			return (TRUE);
		}
	info->flag = idx;
	return (FALSE);
}

t_cmd	*new_t_cmd()
{
	t_cmd	*content;

	if (!(content = ft_calloc(1, sizeof(t_cmd))))
		return (NULL);
	if (!(content->arry = ft_calloc(1, sizeof(char*))))
		return (NULL);
	return (content);
}

t_cmd	*cmd_set_semi_case(t_cmd *content, t_list **cmd_set,
						t_list *cmd_list, t_info *info)
{
	if (info->flag - info->start)
		content->arry = add_double_str(content->arry,
										ft_substr(info->cmd[info->idx],
										info->start,
										info->flag - info->start));
	content->flag = ft_strdup(";");
	ft_lstadd_back(&(*cmd_set), ft_lstnew(content));
	content = NULL;
	if ((info->idx + 1 != double_str_len(info->cmd)) ||
	info->flag < (int)ft_strlen(info->cmd[info->idx] + info->flag) - 1)
	{
		content = new_t_cmd();
		*cmd_set = ft_lstnew(NULL);
		ft_lstadd_back(&(cmd_list), ft_lstnew(*cmd_set));
	}
	info->start = info->flag + 1;
	return (content);
}

t_cmd	*cmd_set_other_case(t_cmd *content, t_list *cmd_set, t_info *info)
{
	if (info->flag - info->start)
		content->arry = add_double_str(content->arry,
										ft_substr(info->cmd[info->idx],
										info->start,
										info->flag - info->start));
	if (info->flag_is_double)
	{
		content->flag = ft_substr(info->cmd[info->idx], info->flag, 2);
		info->start = info->flag + 2;
	}
	else
	{
		content->flag = ft_substr(info->cmd[info->idx], info->flag, 1);
		info->start = info->flag + 1;
	}
	ft_lstadd_back(&(cmd_set), ft_lstnew(content));
	content = NULL;
	if ((info->idx + 1 != double_str_len(info->cmd)) ||
	info->flag < (int)ft_strlen(info->cmd[info->idx] + info->flag) - 1)
		content = new_t_cmd();
	return (content);
}

t_list	*set_cmd_list(char **cmd,
						t_list *cmd_set_list,
						t_list *cmd_set,
						t_cmd *content)
{
	t_info	info;

	info.idx = -1;
	info.cmd = cmd;
	while (cmd[++info.idx])
		if (cmd[info.idx][0] == '\'' || cmd[info.idx][0] == '\"')
			content->arry = add_double_str(content->arry, ft_strdup(cmd[info.idx]));
		else
		{
			info.start = 0;
			while (check_flag(cmd[info.idx], &info) &&
					info.start < (int)ft_strlen(cmd[info.idx]))
				if (cmd[info.idx][info.flag] == ';')
					content = cmd_set_semi_case(content, &cmd_set,
													cmd_set_list, &info);
				else
					content = cmd_set_other_case(content, cmd_set, &info);
			if (info.flag - info.start)
				content->arry = add_double_str(content->arry,
				ft_substr(cmd[info.idx], info.start, info.flag - info.start));
		}
	if (content)
		ft_lstadd_back(&(cmd_set), ft_lstnew(content));
	return cmd_set_list;
}

t_list	*get_cmd_list(char **cmd)
{
	t_list	*cmd_set_list;
	t_list	*cmd_set;
	t_cmd	*content;

	// 초기화
	cmd_set = ft_lstnew(NULL);
	content = new_t_cmd();
	cmd_set_list = ft_lstnew(cmd_set);
	return (set_cmd_list(cmd, cmd_set_list, cmd_set, content));
}
