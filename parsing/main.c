/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:37:42 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 13:17:24 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	minishell(t_shell *shell)
{
	while (1)
	{
		signal(SIGINT, handle_signal);
		shell->input_L = readline("meowshell> ");
		if (shell->input_L && shell->input_L[0] != '\0')
			add_history(shell->input_L);
		if (!shell->input_L)
			break ;
		else if (shell->input_L[0] != '\0')
		{
			shell->parse_fail_L = parser(shell);
			parse_end(shell);
	}
		else if (shell->input_L[0] == '\0')
			write(2, "empty line\n", 11);
		free(shell->input_L);
		free_cmds(shell);
	}
}

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_sig = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)av;
	if (ac != 1)
		return (printf("'./minishell' only, no arguments\n"));
	ft_bzero(&shell, sizeof(t_shell));
	initialize_shell(&shell);
	get_env(&shell, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	minishell(&shell);
	write(1, "exit\n", 5);
	free_all(&shell);
}

// { }, { }, { }

//    echo    hello   " my   friend   "
// j = 28  i = 33

// \033[1;31m	               7 (Escape sequence for red)
// 	environment malloc fail	   24 (Plain text)
// 	\033[0m             	   4 (Reset color)
// 	\n	                       1 (Newline)