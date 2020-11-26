#include "minishell.h"


void	prompt()
{
	ft_putstr_fd("minishell >", 1);
}

void	fun(char **envp, t_list **cmd_list)
{
	// 달러 처리를 한다?
}


int		main(int argc, char **argv, char **envp)
{
	// init
	ft_first_envv(&envp);
	// 새로운 envp 가된다.


	/*i
	  입력받는 무한루프
	  	입력받기
		  어떤 명령어인지
		  		프로세스를 만들어야 한다.
					1. |
					2. 외부 프로그램
				안만들어도 됨
					1. | 없음
					2. 

	1. 프롬프트에서 명령문을 작성한후 enter 키
	2. 명령문을 token(단어) 로 분리
	3. 해석해야할 표현식이 있는 경우
		변수확장
		산술확장
		명령치환
	4. 최종 명령문 완성
	5. 불필요한 quote 삭제처리
	*/
}