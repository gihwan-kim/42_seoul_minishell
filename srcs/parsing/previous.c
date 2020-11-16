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
char	**cmd_parsing(char *str, char *quote_ptr, char c)
{
	char	**ret;
	char	**next;
	char	tmp;

	ret = NULL;
	if (!(ret = ft_calloc(1, sizeof(char*))))
		return (ret);
	ret[0] = 0;
	while (quote_ptr)
	{
		*quote_ptr = 0;
		// cur = ret;

		// ', " 가 없다면
		// ', "  생기기 전까지 split 해서 만들어두고
		next = ft_split(str, ' ');
		ret = make_word(ret, next);
		*quote_ptr = c;
		str = quote_ptr;
		quote_ptr = ft_strchr(str + 1, c);
		// ' 가 하나밖에 없으니까 에러
		if (!quote_ptr)
			return (NULL);
		tmp = *(quote_ptr + 1);
		*(quote_ptr + 1) = 0;
		next = ft_split(str, '\0');
		*(quote_ptr + 1) = tmp;
		ret = make_word(ret, next);
		str = quote_ptr + 1;
		quote_ptr = ft_strchr(str, c);
	}
	next = ft_split(str, ' ');
	ret = make_word(ret, next);
	return (ret);
}

char	**ft_mininsplit(char *str)
{
	char	**ret;
	char	*s_quote_ptr;
	char	*d_quote_ptr;

	ret = NULL;
	s_quote_ptr = ft_strchr(str, '\'');
	d_quote_ptr = ft_strchr(str, '\"');
	printf("|%s| |%p|\n", s_quote_ptr, s_quote_ptr);
	printf("|%s| |%p|\n", d_quote_ptr, d_quote_ptr);
	if (s_quote_ptr || d_quote_ptr)
	{
		// ' 가 더 앞일 경우 '""' or ' '
		if (s_quote_ptr - d_quote_ptr < 0)
			ret = cmd_parsing(str, s_quote_ptr, '\'');
		// " 가 앞일 경우 "''" or ""
		else
			ret = cmd_parsing(str, d_quote_ptr, '\"');
	}
	else
		ret = ft_split(str, ' ');
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
	printf("|%s|\n", check);
	ret = ft_mininsplit(check);
	if (!ret)
		printf("error\n");
	printf("reslut \n");
	while (ret[idx])
	{
		printf("%s\n", ret[idx]);
		idx++;
	}
}
