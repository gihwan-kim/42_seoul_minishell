#include "minishell.h"

void	free_program(void *content)
{
	t_cmd *command;

	command = (t_cmd*)content;
	if (command)
		free_double_str(command->program);
	free(command);
}

t_list *ft_parsing(char *str)
{
	t_list *ret;

	t_cmd	*content;
	int		i;		// str index
	int		j;		// buff index
	char	flag;
	char	*buff;	// 문자"문자" 같이 quote 앞에 다른게 있을 경우 임시로 저장해두는 배열

	flag = 0;

	j = 0;
	ret = ft_lstnew(NULL);
	buff = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	content = ft_calloc(1, sizeof(t_cmd));
	i = -1;
	int count = 0;
	while (str[++i])
		if (str[i] == ' ')
			count++;
	content->program = ft_calloc(count + 2, sizeof(char*));
	int p_i;

	p_i = 0;
	i = -1;

	// flag : 0 , 아직 quote안나옴 -> str[i] 가 quote 랑 같을 경우
	// flag 에 quote 넣기
	// str[i] 에서 flag 랑 같은 값이 나오면 flag 0
	while (str[++i])
	{
		if (str[i] == flag)
			flag = 0;
		else if (flag == 0 && str[i] == '\'')
			flag = '\'';
		else if (flag == 0 && str[i] == '\"')
			flag = '\"';
		// ; 0, | 1, > 2 , >> 3, < 4
		else if (flag == 0 && ft_strchr(";|><", str[i]))
		{
			if (str[i] == ';')
				content->flag = 0;
			else if (str[i] == '|')
				content->flag = 1;
			else if (str[i] == '>')
			{
				if (str[i + 1] == '>')
					content->flag = 2;
				else
					content->flag = 3;
			}
			else
				content->flag = 4;
			// 기존  t_cmd 리스트에 추가
			ft_lstadd_back(&(ret), ft_lstnew(content));
			// 새로운 t_cmd 생성
			content = ft_calloc(1, sizeof(t_cmd));
			content->program = ft_calloc(count + 2, sizeof(char*));
			p_i = 0;
		}
		else if (flag == 0 && str[i] == ' ')
		{
			if (*buff)
			{
				content->program[p_i] = ft_strdup(buff);
				content->program[p_i + 1] = NULL;
				p_i++;
				ft_bzero(buff, ft_strlen(buff) + 1);
				j = 0;
			}
		}
		else
		{
			buff[j] = str[i];
			j++;
		}
	}
	// 버퍼에 남은것 넣기
	if (*buff)
	{
		content->program[p_i] = ft_strdup(buff);
		content->program[p_i + 1] = NULL;
		ft_lstadd_back(&(ret), ft_lstnew(content));
	}
	// 해제
	free(buff);

	// 에러확인
	if (flag != 0)
	{
		ft_lstclear(&(ret), free_program);
		//error
		// 리스트 해제
		ret = 0;
	}

	return (ret);
}
