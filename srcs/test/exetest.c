#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
	1. 프롬프트에서 명령문을 작성한후 enter 키
	2. 명령문을 token(단어) 로 분리
	5. 불필요한 quote 삭제처리

	3. 해석해야할 표현식이 있는 경우
		변수확장
		산술확장
		명령치환
	4. 최종 명령문 완성

	1. parsing.c -> 입력을 받아서 링크드 리스트 구조체를 만들어주는 함수
		1-1 입력된 구조체를 환경변수로 치환
	2. parsing.c에서 끝난 결과물을 처리할 수 있도록 플래그에 따라
		fork 및 파이프라인 설정 및 출력을 할 수 있도록 하는 모듈
	3. ft_execve.c -> 이중포인터넘기면 프로그램 실행


*/


/*
출처: https://www.it-note.kr/157 [IT 개발자 Note]

    int execve(const char *filename,
                char *const argv[], 
                char *const envp[]);
    /현재 실행중인 프로세스는 사라지고 filename 프로그램을 메모리에 올림

    exec 함수에서 
        v : argv가 vector(배열)로 parameter를 하나를 받는다는 의미입니다. 배열의 마지막값은 NULL
        e : 설정할 환경변수를 parameter로 받는다는 의미입니다.

    filename
        - 교체할 실행 파일 / 명령어.
        - filename은 실행가능한 binary이거나 shell이어야 합니다.
        - filename은 path가 설정되어 있는 디렉토리라고 하더라도 
        절대path나 상대path로 정확한 위치를 지정해야 합니다.
    argv
        - c언어의 main(int argc, char *argv[])에서 argv와 비슷하며, main함수에는 argc가 있지만 
        execve에는 argc가 없으므로 main의 argv에 마지막 array 다음은 NULL이어야 있는 것과 같습니다.
    envp
        - key=value형식의 환경변수 문자열 배열리스트로 마지막은 NULL이어야 합니다.
        - 만약 기 설정된 환경변수를 사용하려면 environ 전역변수를 그냥 사용합니다.

	return 
		없음 : 정상적으로 프로그램이 실행됨, 리턴값은 이미 지정된 프로그램의 로직으로 실행됨
		-1  : 상세한 오류는 errno 전역 변수에 설정된다.

	execve 함수로 외부 프로그램을 돌렸을때
		bash가 에러, 성공 이 정도만 판단을 하는지?
		bash가 프로그램의 성공한 특정 값까지 받아오는지?

*/

int main(int argc, char **argv, char **envp)
{
	int stat_loc;
	// int status;
	char *arr[] = {"/Users/gihkim/cs/42cursus/42_seoul_minishell/srcs/re3", "-al", NULL};
	pid_t child_pid;
	// if (!(child_pid = fork()))
	// {
	// 	exit(11111);
	// 	// -> 실행이 안됨
	// }
	// wait(&status);
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(arr[0], arr, envp);
		exit(111); // 덮어씌워지니까 실행안됨
		printf("child!\n");
	}
	else if(child_pid > 0)
	{
			wait(&stat_loc);
			printf("parent! %d\n", stat_loc % 256);
	}
	else
	{
		/* error */
	}

	// printf("status: %d\n", status);
	// printf("errno: %d\n", errno);
	return (0);
}
