/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:34:39 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/04 00:12:35 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt()
{
	ft_putstr_fd("minishell$ ", 1);
}

int		g_exit_status = 0;
char	**envp = NULL;

int		minishell()
{
	t_list	*cmd_list;
	char	*line;

	line = NULL;
	while (1)
	{
		prompt();
		get_next_line(0, &line);
		if ((cmd_list = parsing_first(line)))
		{
			printf("first parsing end\n");
			ft_lstiter(cmd_list->next, print);
			controller(cmd_list);
		}
		else
		{
			continue;
		}
	}
}

int		main(int argc, char **argv, char **envv)
{
	(void)argc;
	(void)argv;

	// signal(SIGINT, SIG_IGN); // ctr + c 무시하겠다는 신호

	// init
	// 새로운 envv 가된다.
	envp = ft_first_envv(envv);

	// signall check
	minishell();
}