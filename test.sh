
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
    # printf $@\n
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
    printf "\ncomamnd : |$1|\n"
    # 2 (표준에러가 표준 출력을 가리키게 하고 표준 출력은 삭제)
    # printf $@\n
    BASH_OUTPUT=$(echo $1 "; exit" | bash 2>&-)
    BASH_EXIT_STATUS=$?
    MINI_OUTPUT=$(echo $2 "; exit" | ./minishell 2>&-)
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

function file() {

    printf "[\tECHO\t]\n\n\n"

    # ECHO
    test 'echo -n fsadf echo a'
    test 'echo -n -nnn hello -n ; echo a'
    test 'echo '"abc"''
    test 'echo bonjour'
    test 'echo[TAB]a'
    test 'echo\ a'
    test 'echo "\s" ; echo "\\s"'
    test 'echo "12\""'
    test 'echo "bip | bip ; coyotte > < \" "'
    test 'echo \>''1'
    test 'echo $USER$var\$USER$USER\$USERtest$USER'
    test 'echo bonjour \; ls'

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
    test 'export $var=test avec var unset'
    test 'export la même variable'
    test 'export var puis export var=test'
    test 'export "" test=a'
    test 'export "" test=a puis env'
    test 'export ""  et unset ""'
    test 'export "test=ici"=coucou ; echo $test'
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

    mkdir test_file/trunc
    mkdir test_file/append
    mkdir test_file/multi

    trunc_mini=./test_file/trunc/mini
    trunc_bash=./test_file/trunc/bash
    mkdir $trunc_bash $trunc_mini

    append_mini=./test_file/append/mini
    append_bash=./test_file/append/bash
    mkdir $append_bash $append_mini
    cp -r ./test_folder/ $append_bash

    multi_mini=./test_file/multi/mini
    multi_bash=./test_file/multi/bash
    mkdir $multi_bash $multi_mini
    # > trunc
    test_redirection 'echo test test test > $trunc_bash/bash_1; cat $trunc_bash/bash_1'  'echo test test test > $trunc_mini/mini_1 ; cat $trunc_mini/mini_1'
    test_redirection 'ls -al > $trunc_bash/bash_2; cat $trunc_bash/bash_2'  'ls -al > $trunc_mini/mini_2; cat $trunc_mini/mini_2'
    test_redirection 'echo ABC !$PATH >  $trunc_bash/bash_3 >  $trunc_bash/bash_3; cat  $trunc_bash/bash_3' 'echo ABC !$PATH >  $trunc_mini/mini_3 >  $trunc_mini/mini_3; cat  $trunc_mini/mini_3'
    test_redirection 'env > $trunc_bash/bash_4 ; cat $trunc_bash/bash_4' 'env > $trunc_mini/mini_4 ; cat $trunc_mini/mini_4'
    test_redirection 'env > $trunc_bash/bash_trash1 > $trunc_bash/bash_trash2 > $trunc_bash/bash_5 ; cat $trunc_bash/bash_5' 'env > $trunc_mini/mini_trash1 > $trunc_mini/mini_trash2 > $trunc_mini/mini_5 ; cat $trunc_mini/mini_5'

    # >> append
    test_redirection 'ls -al >> $append_bash/append_1 ; cat $append_bash/append_1' 'ls -al >> $append_mini/append_1 ; cat $append_mini/append_1'
    test_redirection 'cat Makefile >> $append_bash/append_2 ; cat $append_bash/append_2' 'ls -al >> $append_mini/append_2 ; cat $append_mini/append_2'
    test_redirection 'cat Makefile >> $append_bash/trash_1 >> $append_bash/trash_2 ; cat $append_bash/append_3' 'cat Makefile >> $append_mini/trash_1 >> $append_mini/trash_2 ; cat $append_mini/append_3'

    # < read
    test_redirection 'cat -e < Makefile' 'cat -e < Makefile'
    test_redirection 'cat -e < ./srcs/main.c < Makefile' 'cat -e < ./srcs/main.c < Makefile'

    # multi
    test_redirection 'cat -e < ls > $multi_bash/1; cat $multi_bash/1' 'cat -e < ls > $multi_mini/1; cat $multi_mini/1'
    test_redirection '< Makefile cat > $multi_bash/2 ; cat $multi_bash/2' '< Makefile cat > $multi_mini/2 ; cat $multi_mini/2'
    test_redirection '< ls > $multi_bash/3 ; cat $multi_bash/3' '< ls > $multi_mini/3 ; cat $multi_mini/3'

    # SYNTAX ERROR
    test 'echo bonjour ; |'
    test 'echo bonjour > > out'
    test 'echo bonjour > $test'
    test 'echo bonjour > $test w/ test="o1 o2"'
    test 'echo bonjour >>> test'
    test 'echo bonjour | |'
    test 'echo bonjour |;'

    rm -r  a 
}
rm result.txt
printf "wait......\n"
file > result.txt