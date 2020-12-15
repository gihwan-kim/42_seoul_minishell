/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 23:10:37 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/11 14:04:35 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../lib/libft/libft.h"
#include "../lib/libft/get_next_line.h"
#include "data.h"
#include "utils.h"
#include "error.h"
#include "builtin.h"
#include "command.h"
#include "parsing.h"
# define FALSE 0
# define TRUE 1 
# define ERROR 0
# define SUCCESS 1
# define ERROR_P NULL
# define BASH_SUCCESS 0
# define BASH_ERR_NOL 1
# define BASH_ERR_SYN 2 // 잘못 사용된 builtin 명령, syntax error
# define BASH_ERR_EXE 126 // 명령 실행 불가, 명령은 존재하지만 excutable 이 아니거나 퍼미션 문제
# define BASH_ERR_NOF 127 // not found, 파일이 존재하지 않음
# define VERSION "0.0.0"
#endif
