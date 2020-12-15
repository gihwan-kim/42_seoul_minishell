/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmai.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:34:39 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/15 13:00:49 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;
int		g_signal = 1;
char	**g_envp = NULL;

void	prompt()
{
	ft_putstr_fd("minishell-", STDERR_FILENO);
	ft_putstr_fd(VERSION, STDERR_FILENO);
	ft_putstr_fd("$ ", STDERR_FILENO);
}

void handler(int signo)
{
	(void)signo;
	g_exit_status = 1;
	write(STDERR_FILENO, "\b\b", 2);
	if (signo != SIGTERM)
		write(STDERR_FILENO, "  \n", 3);
	if (g_signal)
		prompt();
}

int		minishell()
{
	t_list	*cmd_list;
	char	*line;
	
	line = NULL;
	while (1)
	{
		prompt();
		if (!get_next_line(0, &line) && !ft_strlen(line))// ctrl + d
		{
			g_signal = 0;
			ft_putendl_fd("exit", STDERR_FILENO);
			free(line);
			exit(BASH_SUCCESS);
		}
		else if ((cmd_list = parsing_first(line)))
		{
			g_signal = 0;
			controller(cmd_list);
		}
		free(line);
		g_signal = 1;
	}
}

int		main(int argc, char **argv, char **envv)
{
	(void)argc;
	(void)argv;
	g_envp = ft_first_envv(envv);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGTERM, handler);
	minishell();
}