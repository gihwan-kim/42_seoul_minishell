/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_second.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:34:42 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/02 14:22:47 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern	int	g_exit_status;

char		*find_env(char *str, int *i)
{
	char	*ret;
	int		start;
	int		idx;

	idx = *i + 1;
	start = *i + 1;
	while (str[idx])
		if (ft_isalnum(str[idx]) || str[idx] == '_')
			idx++;
		else
		{
			idx--;
			break;
		}
	*i = idx;
	ret = ft_substr(str, start, idx - start + 1);
	return (ret);
}

int			set_env_to_buf(const char **envv, char *env, char *buf)
{
	int		i;

	i = -1;
	while (envv[++i])
	{
		if (check_unset(env, (char*)envv[i]))
		{
			ft_strlcat(buf,
						(char*)envv[i] + ft_strlen(env) + 1,
						ft_strlen(envv[i]) + ft_strlen(buf));
			break ;	
		}
	}
	free(env);
	return ((int)ft_strlen(buf));
}

void		set_exit_status_to_buf(char *buf)
{
	char	*status;
	int		idx;

	idx = 0;
	status = ft_itoa(g_exit_status);
	ft_strlcat(buf, status, ft_strlen(buf) + ft_strlen(status) + 1);
}

char		*word_parsing(char **program, int *idx, const char **envp, char *buf)
{
	char	quote;
	int		j;	// word index
	int		i;	// buff index

	i = -1;
	quote = 0; // quote == 0 : quote 사이에 속해있지 않는 문자
	j = 0;
	while (program[*idx][++i]) // 문자 하나씩 돌면서 체크
		if (program[*idx][i] == quote)			// quote 시작
			quote = 0;
		else if (quote == 0 && (program[*idx][i] == '\'' || program[*idx][i] == '\"'))
			quote = program[*idx][i];			// quote 닫는 부분
		else if (quote == '\"' && program[*idx][i] == '\\' && program[*idx][i + 1]) //|| ft_strchr("\"$`\\", program[*idx][i + 1])
			buf[j++] = program[*idx][++i];		// double quote escape
		else if (quote == 0 && program[*idx][i] == '\\' && program[*idx][i + 1])
			buf[j++] = program[*idx][++i];		// no quote escape
		else if (quote != '\'' && program[*idx][i] == '$' && program[*idx][i + 1]) // double quote 또는 no quote 에서 $ 처리
			if (program[*idx][i + 1] == '?' && (i += 2))
				set_exit_status_to_buf(buf);
			else						// 환경변수 값 찾아서 넣어주기
				j = set_env_to_buf(envp, find_env(program[*idx], &i), buf);
		else							// 일반 문자
			buf[j++] = program[*idx][i];
	free(program[*idx]);
	return(ft_strdup(buf));
}

char		*word_parsing_splitting(char **program, int *idx, const char **envp, char *buf)
{
	char	quote;
	int		j;	// word index
	int		i;	// buff index

	i = -1;
	quote = 0;							// quote == 0 : quote 사이에 속해있지 않는 문자
	j = 0;
	while (program[0][++i])					// 문자 하나씩 돌면서 체크
		if (program[0][i] == quote)			// quote 시작
			quote = 0;
		else if (quote == 0 && (program[0][i] == '\'' || program[0][i] == '\"'))
			quote = program[0][i];			// quote 닫는 부분
		else if (quote == '\"' && program[0][i] == '\\' && program[0][i + 1]) //|| ft_strchr("\"$`\\", program[0][i + 1])
			buf[j++] = program[0][++i];		// double quote escape
		else if (quote == 0 && program[0][i] == '\\' && program[0][i + 1])
			buf[j++] = program[0][++i];		// no quote escape
		else if (quote != '\'' && program[0][i] == '$' && program[0][i + 1]) // double quote 또는 no quote 에서 $ 처리
			if (program[0][i + 1] == '?' && (i += 2))
				set_exit_status_to_buf(buf);
			else						// 환경변수 값 찾아서 넣어주기
			{
				j = set_env_to_buf(envp, find_env(program[0], &i), buf);
				if (quote != '\"')
					*idx = 1;
			}
		else							// 일반 문자
			buf[j++] = program[0][i];
	free(program[0]);
	return(ft_strdup(buf));
}

// program 의 요소들 반복하며 $, escape 체크하고 새롭게 생성해줌
// dollar escpae 처리
char		**parsing_second(char **program, const char **envp)
{
	char	*tmp;
	char	buf[100000];;
	int		idx; 

	idx = -1;
	ft_memset(buf, 0, 100000);
	if (double_str_len(program) == 1)
	{
		program[0] = word_parsing_splitting(program, &idx, envp, buf);
		if (idx == 1)
		{
			tmp = program[0];
			program = ft_split(tmp, '/');
			free(tmp);
		}
	}
	else
	{
		while (program[++idx])
		{
			program[idx] = word_parsing(program, &idx, envp, buf);
			ft_memset(buf, 0, 100000);
		}
	}
	return (program);
}




// char	*word_parsing(char **program, int *idx, const char **envp, char *buf)
// {
// 	char	quote;
// 	char	*word;
// 	int		j;	// word index
// 	int		i;	// buff index

// 	i = -1;
// 	word = program[*idx];
// 	quote = 0; // quote == 0 : quote 사이에 속해있지 않는 문자
// 	j = 0;
// 	while (word[++i]) // 문자 하나씩 돌면서 체크
// 		if (word[i] == quote)			// quote 시작
// 			quote = 0;
// 		else if (quote == 0 && (word[i] == '\'' || word[i] == '\"'))
// 			quote = word[i];			// quote 닫는 부분
// 		else if (quote == '\"' && word[i] == '\\' && word[i + 1]) //|| ft_strchr("\"$`\\", word[i + 1])
// 			buf[j++] = word[++i];		// double quote escape
// 		else if (quote == 0 && word[i] == '\\' && word[i + 1])
// 			buf[j++] = word[++i];		// no quote escape
// 		else if (quote != '\'' && word[i] == '$' && word[i + 1]) // double quote 또는 no quote 에서 $ 처리
// 			if (word[i + 1] == '?')
// 			{
// 				set_exit_status_to_buf(buf);
// 				i += 2;
// 			}
// 			else						// 환경변수 값 찾아서 넣어주기
// 				j = set_env_to_buf(envp, find_env(word, &i), buf);
// 		else							// 일반 문자
// 			buf[j++] = word[i];
// 	free(program[*idx]);
// 	return(ft_strdup(buf));
// }