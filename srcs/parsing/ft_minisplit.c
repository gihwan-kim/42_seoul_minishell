#include "minishell.h"
/*

""
Double quotes 안에서는 $ ` ! 특수기능을 하는 문자들이 해석되어 실행되고 공백과 개행이 유지됩니다.
변수 사용 시에도 동일하게 적용되므로 quote 을 하지 않으면 공백과 개행이 유지되지 않습니다

''
별다른 기능 없이 모든 문자를 있는 그대로 표시합니다. escape 도 되지 않습니다.
이 안에서 single quotes 을 사용하려면 뒤에 이어지는 $' ' 을 사용해야 합니다.
*/


// 이중 포인터 배열들을 합칠때 복제하고 합쳐줘야함
// 나중에 합치고 나서 free 할때 동일한 메모리를 가리키고 있어서
// 이전 배열들을 free 하면 값이 다사라짐 복제해둬야함

char	**ft_splitjoin(char **split1, char **split2)
{
	char	** ret;
	int		i1;
	int		i2;

	i1 = 0;
	while (split1[i1])
		i1++;
	i2 = 0;
	while (split2[i2])
		i2++;
	if (!(ret = ft_calloc(i2 + i1 + 1, sizeof(char*))))
		return (ret);
	i1 = -1;
	while (split1[++i1])
		ret[i1] = ft_strdup(split1[i1]);
	i2 = -1;
	while (split2[++i2])
		ret[i1 + i2] = ft_strdup(split2[i2]);
	return (ret);
}

// 이중 배열 free 함수
void	free_double_ptr(char **ptr)
{
	int idx;

	idx = 0;
	if (ptr)
	{
		while (ptr[idx])
			free(ptr[idx++]);
		free(ptr);
	}
}

char	**make_word(char **cmd, char **next_word)
{
	char **ret;
	char **cur_word;

	cur_word = cmd;
	ret = ft_splitjoin(cur_word, next_word);
	free_double_ptr(cur_word);
	free_double_ptr(next_word);
	return (ret);
}

// char * -> char **
char	**add_word(char **word_set, char **cmd, char *quote_loc, char seperator)
{
	char	**ret;
	char	**next_words;
	char	*quote_loc_close;
	char	tmp;

	ret = NULL;
	if (!(ret = ft_calloc(1, sizeof(char*))))
		return (ret);
	ret[0] = 0;
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

char	**ft_mininsplit(char *cmd)
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
