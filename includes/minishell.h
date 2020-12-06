/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 23:10:37 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/03 23:53:17 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# define SUCCESS 11
# define ERROR_P NULL


#endif
