
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
    printf "\tBASH_OUTPUT : $1\n"
    printf "\tMINI_OUTPUT : $2\n\n\n"
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
        let " SUCCESS = $SUCCESS + $PLUS "
    else
        let " FAIL = $FAIL + $PLUS "
    fi
    printf "\n\nSCORE  : $SUCCESS/$TOTAL FAIL : $FAIL\n"
}

function file()
{
    # ECHO
    # test 'echo -n fsadf echo a'
    # test 'echo -n -nnn hello -n ; echo a'
    # test 'echo '"abc"''
    # test 'echo bonjour'
    # test 'echo[TAB]a'
    # test 'echo\ a'
    # test 'echo "\s" ; echo "\\s"'
    # test 'echo "12\""'
    # test 'echo "bip | bip ; coyotte > < \" "'
    # test 'echo \>''1'
    # test 'echo $USER$var\$USER$USER\$USERtest$USER'
    # test 'echo bonjour \; ls'

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

    # # PWD
    # test 'pwd'
    # test 'pwd lalala'

    # # EXPORT
    # test 'export var=a ; export $var=test ; echo $var $a'
    # test 'export $var=test avec var unset'
    # test 'export la même variable'
    # test 'export var puis export var=test'
    # test 'export "" test=a'
    # test 'export "" test=a puis env'
    # test 'export ""  et unset ""'
    # test 'export "test=ici"=coucou ; echo $test'
    # test 'export var="cat Makefile | grep >" ; echo $var'

    # # UNSET
    # test 'unset PATH ; echo $PATH'
    # test 'unset PATH ; ls'
    # test 'unset "" test'
    # test 'unset ='
    # test 'unset PWD'
    # test 'unset var'


    # # ENV
    # test 'env puis export puis env'


    # # VARIABLE
    # test '$'
    # test '$LESS$VAR'


    # # PIPE
    # test 'cat | cat | cat | ls'
    # test 'cat Makefile | grep pr | head -n 5 | cd file_not_exit'
    # test 'cat Makefile | grep pr | head -n 5 | hello'
    # test 'ls | exit'
    # test 'sleep 5 | exit'


    # # REDIRECTION
    # <a cat <b <c
    # <a cat <b <c      avec b n'existe pas (ou pas les droits)
    # > test | echo blabla; rm test
    # >a cat <b >>c 
    # >a ls >b >>c >d
    # >a ls <machin >>c >d     avec machin n'exite pas
    # >file
    # cat -e > test1 < test2
    # cat < test
    # echo 2 > out1 >> out2
    # echo 2 >> out1 > out2
    # echo bonjour > test\ 1
    # echo test > file test1
    # not_cmd bonjour > salut

    # # SYNTAX ERROR
    # |
    # echo bonjour ; |
    # echo bonjour > > out
    # echo bonjour > $test
    # echo bonjour > $test w/ test="o1 o2"
    # echo bonjour >>> test
    # echo bonjour | |
    # echo bonjour |;

}

rm result.txt
file > rere.txt