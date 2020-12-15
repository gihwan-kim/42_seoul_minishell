#include "minishell.h"

/*
방법 1.

prasing 실행전에 $ 가 제대로 적용되는 부분 찾아서 큰따옴표로 묶어주기
	-> 새로운 str 생성해줘야함
env=val

1. echo 단어$env단어
	-> echo 단어
2. ' '
	- 걍 문자
3. " "
	-> 달러찾기 바꿔주기
4. 없음
	-> 달러찾기 바꿔주기
4. 없는 환경변수
	-> x
5. 알파벳만 잘라
*/
char	*find_env(char *str, int *i)
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

void	set_env_to_buf(char **envv, char *env, char *buf, int mod)
{
	int		i;

	i = -1;
	while (envv[++i])
	{
		if (check_unset(env, envv[i]))
		{
			if (mod)
				ft_strlcat(buf, envv[i] + ft_strlen(env) + 1, ft_strlen(envv[i]) + ft_strlen(buf));
			else
			{
				buf[ft_strlen(buf)] = '\"';
				ft_strlcat(buf, envv[i] + ft_strlen(env) + 1, ft_strlen(envv[i]) + ft_strlen(buf));
				buf[ft_strlen(buf)] = '\"';
			}
			break ;	
		}
	}
}

char    *str_to_env(char *str, char **envv)
{
    char	buf[100000];
    char	quote;
    int		idx; 
	int		flag;

    idx = -1;
	flag = 0;
	ft_memset(buf, 0, 100000);
    while (str[++idx])
    {
        if (quote == 0 && (str[idx] == '\'' || str[idx] == '\"'))
            quote = str[idx];
        else if (quote == str[idx])
            quote = 0;
		if (str[idx] == '$')
		{
			if (str[idx + 1] == '?')
			{
				// buf 명령어 리턴값 넣어주기
				// 명령어 리턴값을 어디서 어떻게 가져오지?
				idx += 2;
			}
			else
			{
				if (quote == '\"')
				{
					printf("quote double $\n");
					set_env_to_buf(envv, find_env(str, &idx), buf, 1);
				}
					//while로 idx증가시키며 환경변수 찾고 버퍼에 저장
				else if(quote == 0)
					set_env_to_buf(envv, find_env(str, &idx), buf, 0);
					//while로 idx증가시키며 환경변수 찾고 ""감싸며 버퍼에 저장
				else
					buf[ft_strlen(buf)] = str[idx];
			}

		}
		else
			buf[ft_strlen(buf)] = str[idx];
		if (!str[idx])
			break ;
    }
	return (ft_strdup(buf));
}