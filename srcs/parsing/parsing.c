#include "parsing.h"

int		space_count(char *str)
{
	int	count;
	int i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			count++;
		i++;
	}
	return (count);
}

// falg 일 경우 버퍼에 담아둔 문자들을 content 가 가진 program 이중 포인터 배열에 담아준다.
int push_content(t_info *info, t_list *ret, char *str, int wow)
{
	if (wow == 3)
		info->i++;
	info->content->flag = wow;
	// 공백 말고 문자들이 붙어있는 상황에서 flag 에 의해
    // 명령어 묶음이 끝날 경우 버퍼에 남아있는 것을 담아주고 버퍼 비우기
    // ex) cmd arg;cmd arg;
	if (*(info->buff))
	{
		info->content->program[info->p_i] = ft_strdup((info->buff));
		info->content->program[info->p_i + 1] = NULL;
		(info->p_i)++;
		ft_bzero((info->buff), ft_strlen((info->buff)) + 1);
		info->j = 0;
	}
	// flag 가 나올때마다 content 를 리스트에 추가시켜 줬는데
    // flag 가 연속해서 나열될 경우 버퍼에 문자열이 담기지 않은채로 빈 content 가 생성되어 리스트에
    // 추가되는 것을 방지
	if ((info->content->program)[0] == 0)
		return (ERRROR);
	else
	{
		ft_lstadd_back(&(ret), ft_lstnew((info->content)));
		printf("while i %d str len %lu\n", info->i, ft_strlen(str));
		if (info->i < (int)ft_strlen(str) - 1)
		{
			(info->content) = ft_calloc(1, sizeof(t_cmd));
			(info->content)->program = ft_calloc(space_count(str) + 2, sizeof(char*));
		}
		info->p_i = 0;
	}
	return (SUCCESS);
}

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

t_list *ft_parsing(char *str)
{
	t_list	*ret;
	t_info	info;
	int flag_check;

	ret = NULL;
	if (!(init(&info, &ret, str)))
		return (NULL);
	flag_check = 1;
	// flag : 0 , 아직 quote안나옴 -> str[i] 가 quote 랑 같을 경우
	// flag 에 quote 넣기
	// str[i] 에서 flag 랑 같은 값이 나오면 flag 0
	while (str[++(info.i)])
	{
		// ; 0, | 1, > 2 , >> 3, < 4
		if (str[info.i] == info.quote)
			info.quote = 0;
		else if (info.quote == 0 && (str[info.i] == '\'' || str[info.i] == '\"'))
			info.quote = str[info.i];
		else if (info.quote == 0 && str[info.i] == ';')
			flag_check = push_content(&info, ret, str, 0);
		else if (info.quote == 0 && str[info.i] == '|')
			flag_check = push_content(&info, ret, str, 1);
		else if (info.quote == 0 && str[info.i] == '>' && str[info.i + 1] != '>')
			flag_check = push_content(&info, ret, str, 2);
		else if (info.quote == 0 && str[info.i] == '>' && str[info.i + 1] == '>')
			flag_check = push_content(&info, ret, str, 3);
		else if (info.quote == 0 && str[info.i] == '<')
			flag_check = push_content(&info, ret, str, 4);
		else if (info.quote == 0 && str[info.i] == ' ')
		{
			if (*(info.buff))
			{
				info.content->program[(info.p_i)] = ft_strdup(info.buff);
				info.content->program[(info.p_i) + 1] = NULL;
				(info.p_i)++;
				ft_bzero(info.buff, ft_strlen(info.buff) + 1);
				info.j = 0;
			}
		}
		else
			info.buff[info.j++] = str[info.i];
		if (!flag_check)
			return (parsing_error(&info, ret, SYNTAX_ERROR));
	}
	// cmd ' 일때 방법 1
	// if (*(info.buff) || info.p_i != 0)
	printf("p_i %d\n", info.p_i);
	if (*(info.buff) || info.p_i != 0)
	{ // echo abc ;   echo | abc |  |NULL
		printf("버퍼에 남은게 있거나 ");
		info.content->program[(info.p_i)] = ft_strdup(info.buff);
		info.content->program[(info.p_i) + 1] = NULL;
		ft_lstadd_back(&(ret), ft_lstnew(info.content));
		info.p_i = 0;
	}
	if (info.quote != 0)
	{
		
		// 에러가 발생할 경우 parsing_error 함수를 호출 시키는데
		// 이때 info 의 내용과 list 의 내용을 프리해줘야됨
		// info.content 의 내용을 list 의 content 에 lstadd_back 으로
		// 넣어주는데 lstadd_back 을 사용하지 않고 끝나는 경우가 있음
		// cmd ' 일때 방법 2
		return (parsing_error(&info, ret, QUOTE_ERROR));
	}
	free(info.buff);
	info.buff = 0;
	return (ret);
}

// 정상적으로 리스트에 추가되면 P_i 가 0 이된다.

// echo abc;
// echo abc | abc
// echo "abc|fd'erweqv;f"
// echo "abc|fd'erweqv;f"abc
// echo "abc|fd'erweqv;f"abc;
// echo "abc|fd'erweqv;f"abc|echo
// echo "abc|fd'erweqv;f"abc 
// echo;
// echo 'hioho'hoh
// 문자열뒤에 공백이 있을 경우 지금 에러 발생함 : 11/24 1103
// 길이 비교해서 content 를 생성해주는데 길이가 작을때 끝날 경우 동적할당을 해서 그런듯
//	echo ' sdfaf
// echo ' : 리스트에 추가안되고  info.content 에만 남아있는 경우 info.p_i != 0 인 경우

// 버퍼에 담는다
// 버퍼담긴건 무조건 컨텐츠에 담는다.
// 컨텐츠에 담긴건 무조건 리스트에 담는다.
// 에러 ('하나일 경우 같은.)는 리스트랑 버퍼를 프리한다. 





	
