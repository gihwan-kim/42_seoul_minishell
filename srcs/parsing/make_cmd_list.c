/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:02:29 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/11/19 16:07:32 by gihwan-kim       ###   ########.fr       */
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

int		check_flag(char *word, int *check_flag_is_double, int *flag_loc, int start)
{
	char	*flag_single;
	char	*flag_double;
	int		idx;

	flag_single = "<|;";
	flag_double = ">";
	*check_flag_is_double = FALSE;
	idx = start - 1;
	while (word[++idx])
	{
		if (ft_strchr(flag_single, word[idx]))
		{
			*flag_loc = idx;
			return (TRUE);
		}
		// double flag 의 경우 첫문자가 속하면 다음 word[idx] 도 동일한지 검사
		// 같으면 flag 두개인거고 다르면 한개만 있는 경우
		if (ft_strchr(flag_double, word[idx]))
		{
			*flag_loc = idx;
			if (word[idx] == word[idx + 1])
				*check_flag_is_double = TRUE;
			return (TRUE);
		}
	}
	// flag 가 없는 경우
	*flag_loc = idx;
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

t_list	*make_cmd_list(char **cmd)
{
	t_list	*cmd_set_list;
	t_list	*cmd_set;
	t_cmd	*content;

	int		idx;
	int		flag_loc;
	int		flag_double_check;
	int		start;
	int		ret;

	idx = -1;

	// init
	cmd_set = ft_lstnew(NULL);
	content = new_t_cmd();
	cmd_set_list = ft_lstnew(cmd_set);
	while (cmd[++idx])
	{
		if (cmd[idx][0] == '\'' || cmd[idx][0] == '\"')
			content->arry = add_double_str(content->arry, ft_strdup(cmd[idx]));
		else // quote 가 아닌 것들
		{
			start = 0;
			while ((ret = check_flag(cmd[idx], &flag_double_check, &flag_loc, start) && start < (int)ft_strlen(cmd[idx])))
			{
				if (cmd[idx][flag_loc] == ';')
				{
					// ; 전까지 content 에 추가해주기
					if (flag_loc - start)
					{
						content->arry = add_double_str(content->arry, ft_substr(cmd[idx], start, flag_loc - start));
						content->size = double_str_len(content->arry);
					}
					content->flag = ft_strdup(";");

					ft_lstadd_back(&(cmd_set), ft_lstnew(content));
					content = NULL;

					// 새로추가 다음께 있는지 확인?
					if ((idx + 1 != double_str_len(cmd)) || flag_loc < (int)ft_strlen(cmd[idx] + flag_loc) - 1)
					{
						content = new_t_cmd();
						cmd_set = ft_lstnew(NULL);
						ft_lstadd_back(&(cmd_set_list), ft_lstnew(cmd_set));
					}
						start = flag_loc + 1;
				}
				else
				{
					if (flag_double_check)
					{
						// flag 전까지 content 에 추가해주기
						if (flag_loc - start)
						{
							content->arry = add_double_str(content->arry, ft_substr(cmd[idx], start, flag_loc - start));
							content->size = double_str_len(content->arry);
						}
						content->flag = ft_substr(cmd[idx], flag_loc, 2);

						// content 를 명령 집합에 추가
						ft_lstadd_back(&(cmd_set), ft_lstnew(content));
						content = NULL;

						if ((idx + 1 != double_str_len(cmd)) || flag_loc < (int)ft_strlen(cmd[idx] + flag_loc) - 1)
							content = new_t_cmd();
						start = flag_loc + 2;
					}
					else
					{
						// flag 앞에 다른 문자가 있어야함
						if (flag_loc - start)
						{
							content->arry = add_double_str(content->arry, ft_substr(cmd[idx], start, flag_loc - start));
							content->size = double_str_len(content->arry);
						}
						content->flag = ft_substr(cmd[idx], flag_loc, 1);

						// content 를 명령 집합에 추가
						ft_lstadd_back(&(cmd_set), ft_lstnew(content));
						content = NULL;

						if ((idx + 1 != double_str_len(cmd)) || flag_loc < (int)ft_strlen(cmd[idx] + flag_loc) - 1)
							content = new_t_cmd();
						start = flag_loc + 1;
					}
				}
			}
			if (flag_loc - start)
			{
				content->arry = add_double_str(content->arry, ft_substr(cmd[idx], start, flag_loc - start));
				content->size = double_str_len(content->arry);
			}
		}
	}
	if (content)
		ft_lstadd_back(&(cmd_set), ft_lstnew(content));
	return (cmd_set_list);
}



/* 사용법 */

	// t_list	*cmd_se_list;
	// t_list *cmd_se;

	// cmd_se_list =cmd_set_list;
	// while (cmd_se_list)
	// {
	// 	cmd_se = ((t_list*)(cmd_se_list->content))->next;
	// 	printf("cmd_set_list |%p|\n", cmd_se_list);
	// 	printf("first |%p|\n", (t_list*)(cmd_se_list->content));
	// 	// cmd_se = cmd_set->next;
	// 	while (cmd_se)
	// 	{
	// 		printf("cmd_set_list |%p| cmd_set |%p|\n", cmd_se_list, cmd_se);
	// 		t_cmd *temp;
	// 		char **tmp;
	// 		int k = 0;
	// 		temp = (t_cmd*)(cmd_se->content);
	// 		tmp = temp->arry;
	// 		while(tmp[k])
	// 		{
	// 			printf("최종 |%s|\n", tmp[k]);
	// 			k++;
	// 		}
	// 		printf("flag : |%s| size : |%d|\n", temp->flag, temp->size);
	// 		cmd_se = cmd_se->next;
	// 	}
	// 	cmd_se_list = cmd_se_list->next;
	// }