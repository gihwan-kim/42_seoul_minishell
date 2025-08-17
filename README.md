# minishell
Simple minishell (mini bash).

[![Video Label](http://img.youtube.com/vi/uMszRFxpIVg/0.jpg)](https://youtu.be/uMszRFxpIVg)


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
