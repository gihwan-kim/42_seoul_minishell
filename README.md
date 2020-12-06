# 42_seoul_minishell
간단한 shell 만들기

함수    : 단어_단어
파일    : 명령어(ft), 나머지는 꼴리는대로
변수    : 놈규칙 쓰기




# Project directory

```
includes // header file
    minishell.h // minidshell.h includes all header file
    command.h
    parsing.h
    utils.h
lib
    libft

srcs
// 소스파일
    command
        // command execute source files
    builtin
        // builtin command source files
    parsing
        // read command and parsing
    error
        // handling error
    utils
        // etc, util source files
    main.c 
```


# BUILD

- we use lldb

### vscode 
```
./.vscode folder

    mac : command + shifd + B
or
    make
```
- vscode 에서 launch.json 에서 gdb 를 사용해보려 했는데 맥 os 업데이트 되면서 권한이나 인증서 관련 처리가 너무 까다로워서 1시간 반 넘게 삽질하다 그냥 lldb 로 사용하니까 잘되더라...
- 디버깅할때 첨파일 flag 'g' 를 추가 시켜줘서 디버깅 정보를 전달해줘야한다.
### terminal
``` 
make 
```

# DEBUGGING

### vscode
```
use .vscode folder of project

mac : F5
```