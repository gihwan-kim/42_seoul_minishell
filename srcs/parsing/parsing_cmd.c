#include "minishell.h"
/**
 * < bash 에서 ', " 규칙 >
 * ""
 * Double quotes 안에서는 $ ` ! 특수기능을 하는 문자들이 해석되어 실행되고 공백과 개행이 유지됩니다.
 * 변수 사용 시에도 동일하게 적용되므로 quote 을 하지 않으면 공백과 개행이 유지되지 않습니다
 *
 * ''
 * 별다른 기능 없이 모든 문자를 있는 그대로 표시합니다. escape 도 되지 않습니다.
 * 이 안에서 single quotes 을 사용하려면 뒤에 이어지는 $' ' 을 사용해야 합니다.
 *
*/

/**
 * make_word()		: 이전 split 한 배열과 새로 생성한 split 한 배열을
 * 					  합쳐주고 이전것들을 free 해줌
 */
char	**make_word(char **cmd, char **next_word)
{
	char **ret;
	char **cur_word;

	cur_word = cmd;
	ret = ft_splitjoin(cur_word, next_word);
	free_double_str(cur_word);
	free_double_str(next_word);
	return (ret);
}

// char * -> char **
/**
 * add_word()		: 공백일 경우 공백으로 split 해주고 ', " 일 경우 다음
 * 					  ', " 문자가 없으면 에러 있으면 잘라줌
 */
char	**add_word(char **word_set, char **cmd, char *quote_loc, char seperator)
{
	char	**next_words;
	char	*quote_loc_close;
	char	tmp;

	if (seperator == ' ')
	{
		next_words = ft_split(*cmd, seperator);
		*cmd = quote_loc;
	}
	else
	{
		quote_loc_close = ft_strchr(quote_loc + 1, seperator);
		if (!quote_loc_close)
			return (NULL);
		tmp = *(quote_loc_close + 1);
		*(quote_loc_close + 1) = 0;
		next_words = ft_split(*cmd, 0);
		*(quote_loc_close + 1) = tmp;
		*cmd = quote_loc_close + 1;
	}
	return (make_word(word_set, next_words));
}

/**
 * parsing_cmd()	: gnl 로 입력받은 문자열을 공백, ', " 로 나누는 함수
 */
char	**parsing_cmd(char *cmd)
{
	char	**ret;
	char	*s_quote_loc;
	char	*d_quote_loc;
	char	seperator;
	char	*quote_loc;
	ret = NULL;
	if (!(ret = ft_calloc(1, sizeof(char*))))
		return (ret);
	s_quote_loc = ft_strchr(cmd, '\'');
	d_quote_loc = ft_strchr(cmd, '\"');
	while ((s_quote_loc) || (d_quote_loc))
	{
		if (s_quote_loc && (s_quote_loc - d_quote_loc < 0))
		{
			seperator = '\'';
			quote_loc = s_quote_loc;
		}
		else
		{
			seperator = '\"';
			quote_loc = d_quote_loc;
		}
		*quote_loc = 0;
		ret = add_word(ret, &cmd, quote_loc, ' ');
		*quote_loc = seperator;
		ret = add_word(ret, &cmd, quote_loc, seperator);
		s_quote_loc = ft_strchr(cmd, '\'');
		d_quote_loc = ft_strchr(cmd, '\"');
	}
	ret = add_word(ret, &cmd, NULL, ' ');
	return ret;
}
/*
 test 함수

int main(int argc, char **argv)
{
	char **ret;
	char	*check;
	int idx;
	(void)argc;
	(void)argv;
	idx = 0;

	get_next_line(&check);
	ret = ft_mininsplit(check);
	if (!ret)
		printf("error\n");
	while (ret[idx])
	{
		printf("%s\n", ret[idx]);
		idx++;
	}
}
*/
