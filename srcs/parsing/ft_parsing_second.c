/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_second.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:34:42 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/31 21:08:47 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	double_quote_escape(char c)
{
	if (c == '\'' || c == '\"' || c == '$' || c == 10)
		return (TRUE);
	else
		return (FALSE);
}

/*
** j : word index
** i : buff index
** quote = 0 : not belong to quote string
** pro
*/

char		*word_parsing(char **prgm, int *idx, const char **envp, char *buf)
{
	char	quot;
	int		j;
	int		i;

	init_word_parsing(&quot, &j, &i);
	while (prgm[*idx][++i])
		if (prgm[*idx][i] == quot)
			quot = 0;
		else if (quot == 0 && (prgm[*idx][i] == '\'' || prgm[*idx][i] == '\"'))
			quot = prgm[*idx][i];
		else if (quot == '\"' && prgm[*idx][i] == '\\' && prgm[*idx][i + 1] &&
				double_quote_escape(prgm[*idx][i + 1]))
			buf[j++] = prgm[*idx][++i];
		else if (quot == 0 && prgm[*idx][i] == '\\' && prgm[*idx][i + 1])
			buf[j++] = prgm[*idx][++i];
		else if (quot != '\'' && prgm[*idx][i] == '$' && prgm[*idx][i + 1])
			if (prgm[*idx][i + 1] == '?' && (i += 2))
				set_exit_status_to_buf(buf, &j, &i);
			else
				j = set_env_to_buf(envp, find_env(prgm[*idx], &i), buf);
		else
			buf[j++] = prgm[*idx][i];
	free(prgm[*idx]);
	return (ft_strdup(buf));
}

char		*word_parsing_splitting(char **prgm, int *idx,
									const char **envp, char *buf)
{
	char	quote;
	int		j;
	int		i;

	init_word_parsing(&quote, &j, &i);
	while (prgm[0][++i])
		if (prgm[0][i] == quote)
			quote = 0;
		else if (quote == 0 && (prgm[0][i] == '\'' || prgm[0][i] == '\"'))
			quote = prgm[0][i];
		else if (quote == '\"' && prgm[0][i] == '\\' && prgm[0][i + 1] &&
				double_quote_escape(prgm[0][i + 1]))
			buf[j++] = prgm[0][++i];
		else if (quote == 0 && prgm[0][i] == '\\' && prgm[0][i + 1])
			buf[j++] = prgm[0][++i];
		else if (quote != '\'' && prgm[0][i] == '$' && prgm[0][i + 1])
			if (prgm[0][i + 1] == '?' && (i += 2))
				set_exit_status_to_buf(buf, &j, &i);
			else
				check_split(&j, set_env_to_buf(envp,
						find_env(prgm[0], &i), buf), idx, quote);
		else
			buf[j++] = prgm[0][i];
	free(prgm[0]);
	return (ft_strdup(buf));
}

/*
** parsing_second()
** check $, escpae
*/

char		**parsing_second(char **program, const char **envp)
{
	char	*tmp;
	char	buf[100000];
	int		idx;

	idx = -1;
	ft_memset(buf, 0, 100000);
	if (double_str_len(program) == 1)
	{
		program[0] = word_parsing_splitting(program, &idx, envp, buf);
		if (idx == 1)
		{
			tmp = program[0];
			program = ft_split(tmp, ' ');
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
