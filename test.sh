
#  같은 명령을 실행시켜서 출력 결과, 상태 값을 비교 하기.
chmod 755 minishell

TOTAL=0
SUCCESS=0

FAIL=0
PLUS=1

function exit_status_test() {
    printf "<<<<<<< EXIT STATUS TEST >>>>>>>\n"
    printf "\tBASH_EXIT_STATUS : $1\n"
    printf "\tMINI_EXIT_STATUS : $2\n\n"
    if [ "$1" == "$2" ] 
    then
        return 1
    else
        return 0
    fi
}

function output_test() {

    printf "<<<<<< OUTPUT TEST >>>>>>>\n"
    printf "\t[ BASH_OUTPUT ]\n$1\n"
    printf "\t[ MINI_OUTPUT ]\n$2\n\n\n"
    if [ "$1" == "$2" ] 
    then
        return 1
    else
        return 0
    fi
}

function test() {
    printf "\n\n[ TEST  NO : $TOTAL ]\n"
    printf "\ncomamnd : |$@|\n"

    # 2 (표준에러가 표준 출력을 가리키게 하고 표준 출력은 삭제)
    BASH_OUTPUT=$(echo $@ "; exit" | bash 2>&-)
    BASH_EXIT_STATUS=$?
    MINI_OUTPUT=$(echo $@ "; exit" | ./minishell 2>&-)
    MINI_EXIT_STATUS=$?

    let "TOTAL= $TOTAL + $PLUS"

    # 종료 상태 값 비교
    exit_status_test "$BASH_EXIT_STATUS" "$MINI_EXIT_STATUS"
    ret_exit=$?

    # 실행 결과 비교
    output_test "$BASH_OUTPUT" "$MINI_OUTPUT"
    ret_output=$?

    if [ "$ret_exit" == "1" ] && [ "$ret_output" == "1" ]
    then
        printf "SUCCESS !!\n"
        let " SUCCESS = $SUCCESS + $PLUS "
    else
        printf "FAIL !!\n"
        let " FAIL = $FAIL + $PLUS "
    fi
    printf "\n\nSCORE  : $SUCCESS/$TOTAL FAIL : $FAIL\n"
}


function test_redirection() {
    printf "\n\n[ TEST  NO : $TOTAL ]\n"
    printf "\nbash comamnd : |$1|\n"
    printf "\nmini comamnd : |$2|\n"
    printf "\n\n|$3 $4|\n\n"

    # 2 (표준에러가 표준 출력을 가리키게 하고 표준 출력은 삭제)
    (echo $1 "; exit" | bash 2>&-)
    BASH_EXIT_STATUS=$?
    sleep 0.1
    
    (echo $2 "; exit" | ./minishell 2>&-)
    MINI_EXIT_STATUS=$?
    sleep 0.1
    let "TOTAL= $TOTAL + $PLUS"

    # 종료 상태 값 비교
    exit_status_test "$BASH_EXIT_STATUS" "$MINI_EXIT_STATUS"
    ret_exit=$?

    # 실행 결과 비교
    sleep 0.1
    printf "\t--check redireciton result : used 'diff' command--\n"
    diff $3 $4

    if [ "$ret_exit" == "1" ]
    then
        printf "SUCCESS !!\n"
        let " SUCCESS = $SUCCESS + $PLUS "
    else
        printf "FAIL !!\n"
        let " FAIL = $FAIL + $PLUS "
    fi
    printf "\n\nSCORE  : $SUCCESS/$TOTAL FAIL : $FAIL\n"
}

function file() {

    printf "[\tECHO\t]\n\n\n"

    # ECHO
    test 'echo -n fsadf echo a'
    test 'echo -n -nnn hello -n ; echo a'
    test 'echo '"abc"'; echo "'single quote'"'
    test 'echo $PATH; echo $USER; echo $NOTHING'
    test 'echo bonjour; echo hello; echo namastte'
    test 'echo[TAB]a'
    test 'echo\ a'
    test 'echo "\s" ; echo "\\s"'
    test 'echo "12\""'
    test 'echo "bip | bip ; coyotte > < \" "'
    test 'echo \>''1'
    test 'echo $USER$var\$USER$USER\$USERtest$USER'
    test 'echo bonjour \'
    test 'echo '$USER''
    test 'echo "$USER"'

    test 'echo ''$USER'''
    test 'echo '''$USER''''
    test 'echo $USER=aaa'
    test 'echo $HELLO=aaa'
    test 'echo aa"bb$USER"cc'
    test 'echo aa"bb$USER cc"dd'
    test 'echo aa"bb$USERcc"dd'
    test 'echo "hello$USER_"'
    test 'echo "hello\nman"'
    test 'echo hello\nman'
    test 'echo "hello\ man"'
    test 'ec"""ho""" hello'
    test 'ec"ho" hello'
    test 'ec'ho' hello'
    test 'ec"'ho'" hello'
    test 'echo hello "|" grep h'
    test 'echo hello | grep h'

    printf "[\tCD\t]\n\n\n"

    # CD
    test 'cd ../../../../../.. ; pwd'
    test 'cd /home/user42/ ; pwd'
    test 'cd $HOME/Bureau ; pwd'
    test 'unset HOME; cd ; pwd'
    test 'export HOME= ; cd ; pwd'
    test 'cd too many arguments ; pwd'
    test 'cd ./path_not_found ; pwd'
    test 'cd - ; pwd'
    test 'mkdir a; mkdir a/b; cd a/b; rm -r ../../a; cd .. ; pwd'
    test 'cd home/.. avec CDPATH set à / ; pwd'
    test 'cd home/dir avec CDPATH set à / ; pwd'
    test 'cd . avec CDPATH set ; pwd'
    test 'cd .. avec CDPATH set ; pwd'

    printf "[\tPWD\t]\n\n\n"

    # PWD
    test 'pwd'
    test 'pwd lalala'

    printf "[\tEXPORT\t]\n\n\n"

    # EXPORT
    # 인자가 "" 빈문자열일 경우 bash: export: `': not a valid identifier
    test 'export var=a ; export $var=test ; echo $var $a'
    test 'export var=a ; export $var=test'
    test 'export $var=test avec var unset'
    test 'export $not_thing=test; echo $not_thing'
    test 'export test=test variable=variable; echo $test $variable'
    test 'export var=test; echo $var'
    test 'export "" test=a; echo $test'
    test 'export "" test=a puis env; echo $test'
    test 'export ""  et unset ""'
    test 'export "test=ici"=coucou ; echo $test'
    test 'export var="cat Makefile | grep >"'
    test 'export var="cat Makefile | grep >" ; echo $var'


    printf "[\tUNSET\t]\n\n\n"

    # UNSET
    test 'unset PATH ; echo $PATH'
    test 'unset PATH ; ls'
    test 'unset "" test'
    test 'unset ='
    test 'unset PWD'
    test 'unset var'


    printf "[\tENV\t]\n\n\n"

    # ENV
    test 'env'

    printf "[\tVARIABLE\t]\n\n\n"

    # VARIABLE
    test '$'
    test '$LESS$VAR'

    printf "[\tPIPE\t]\n\n\n"

    # PIPE
    test 'cat | cat | cat | ls'
    test 'cat Makefile | grep pr | head -n 5 | cd file_not_exit'
    test 'cat Makefile | grep pr | head -n 5 | hello'
    test 'ls | exit'
    test 'sleep 5 | exit'


    printf "[\tREDIRECTION\t]\n\n\n"

    # REDIRECTION
    mkdir test_file
    cp -r test_folder/ test_file
    chmod 777 test_file

    mkdir test_file/trunc
    mkdir test_file/append
    mkdir test_file/multi
    mkdir test_file/read

    trunc_mini=./test_file/trunc/mini
    trunc_bash=./test_file/trunc/bash
    mkdir $trunc_bash $trunc_mini
    chmod 777 $trunc_bash
    chmod 777 $trunc_mini

    append_mini=./test_file/append/mini
    append_bash=./test_file/append/bash
    mkdir $append_bash $append_mini
    cp -r ./test_folder/ $append_bash
    cp -r ./test_folder/ $append_mini
    chmod 777 $append_bash
    chmod 777 $append_mini

    multi_mini=./test_file/multi/mini
    multi_bash=./test_file/multi/bash
    mkdir $multi_bash $multi_mini
    chmod 777 $multi_bash
    chmod 777 $multi_mini

    read_mini=./test_file/read/mini
    read_bash=./test_file/read/bash
    mkdir $read_bash $read_mini
    chmod 777 $read_bash
    chmod 777 $read_mini

    # > trunc

    printf "##\tTRUNC : > \t\n\n\n"

    test_redirection "echo test test test > $trunc_bash/bash_1"  "echo test test test > $trunc_mini/mini_1 " "$trunc_bash/bash_1" "$trunc_mini/mini_1"
    test_redirection "ls -al > $trunc_bash/bash_2 " "ls -al > $trunc_mini/mini_2" "$trunc_bash/bash_2"  "$trunc_mini/mini_2"
    test_redirection "echo ABC !$PATH >  $trunc_bash/bash_3_1 >  $trunc_bash/bash_3_2" "echo ABC !$PATH >  $trunc_mini/mini_3_1 >  $trunc_mini/mini_3_2" "$trunc_bash/bash_3_2" "$trunc_mini/mini_3_2"
    test_redirection "env > $trunc_bash/bash_4 " "env > $trunc_mini/mini_4 " "$trunc_bash/bash_4" "$trunc_mini/mini_4"
    test_redirection "env > $trunc_bash/bash_trash1 > $trunc_bash/bash_trash2 > $trunc_bash/bash_5 " "env > $trunc_mini/mini_trash1 > $trunc_mini/mini_trash2 > $trunc_mini/mini_5 " "$trunc_bash/bash_5" "$trunc_mini/mini_5"

    # >> append

    printf "##\tAPPEND : >> \t\n\n\n"

    test_redirection "ls -al >> $append_bash/append_1 " "ls -al >> $append_mini/append_1 " "$append_bash/append_1" "$append_mini/append_1"
    test_redirection "cat Makefile >> $append_bash/append_2 " "cat Makefile >> $append_mini/append_2 " "$append_bash/append_2" "$append_mini/append_2"
    test_redirection "cat Makefile >> $append_bash/trash_1 >> $append_bash/trash_2 " "cat Makefile >> $append_mini/trash_1 >> $append_mini/trash_2 " "$append_bash/append_3" "$append_mini/append_3"

    # < read

    printf "##\tREAD : < \t\n\n\n"

    test_redirection "cat -e < Makefile > $read_bash/Makefile_copy" "cat -e < Makefile > $read_mini/Makefile_copy" " $read_bash/Makefile_copy"  "$read_mini/Makefile_copy"
    test_redirection "cat -e < Makefile < ./srcs/main.c > $read_bash/main_c_copy" "cat -e < Makefile < ./srcs/main.c > $read_mini/main_c_copy" "$read_bash/main_c_copy" "$read_mini/main_c_copy"
    test_redirection "cat -e < Makefile < ./srcs/main.c < ./srcs/utils/double_ptr_utils.c > $read_bash/double_ptr_utils_copy" "cat -e < Makefile < ./srcs/main.c < ./srcs/utils/double_ptr_utils.c > $read_mini/double_ptr_utils_copy"  "$read_bash/double_ptr_utils_copy" "$read_mini/double_ptr_utils_copy"

    # multi

    printf "##\tMULTI REDIRECTION\t\n\n\n"

    test_redirection "cat -e < test.sh > $multi_bash/1" "cat -e < test.sh > $multi_mini/1" "$multi_bash/1" "$multi_mini/1"
    test_redirection "< Makefile cat > $multi_bash/2 " "< Makefile cat > $multi_mini/2 " "$multi_bash/2" "$multi_mini/2"
    test_redirection "cat < Makefile -e > $multi_bash/3 " "cat < Makefile -e > $multi_mini/3 " "$multi_bash/3" "$multi_mini/3"

    # SYNTAX ERROR
    # bash, minishell 에 접속해서 테스트하기

    ## SEMICOLON ERROR
    # 'echo ; ; ; ;;;;'

    # ## built in error
    # 'cd not found'

    # ## REDIRECTION ERROR
    # ' echo > <'
    # 'echo | |'
    # '<'
    # 'echo SYNTAX_ERROR > > out'
    # 'echo SYNTAX_ERROR > '
    # 'echo SYNTAX_ERROR >>> test'

    # ## PARSING ERROR
    # echo hello ' wow my name is "

    # ## PIPE ERROR
    # 'echo SYNTAX_ERROR | |'
    # '| test'

    # echo 'qqq\'

    rm -r a test_file
}

rm -r test_file
rm result.txt
printf "wait......\n"
file > result.txt
