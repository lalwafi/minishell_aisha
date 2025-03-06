/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:16:43 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 20:02:40 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_shell *shell)
{
	int	i;

	i = 0;
	if (syntax_check(shell) == FALSE)
		return (1);
	else
	{
		if (g_sig != 0)
		{
			shell->exit_code = 1;
			g_sig = 0;
		}
		shell->input_L = ft_strtrim_free(expand_them_vars(\
			shell->input_L, shell), " ");
		shell->input_L = rmv_extra_spaces(shell->input_L);
		shell->num_of_cmds = count_pipes(shell->input_L) + 1;
		shell->pipe_split_L = split_pipes(shell->input_L, '|');
		if (!shell->pipe_split_L)
			(free_all(shell), \
			write(2, "\033[0;31mError: malloc fail\033[0m\n", 24), \
			exit(EXIT_FAILURE));
		while (shell->pipe_split_L[i])
			tokenize_it(shell, shell->pipe_split_L[i++], 0);
	}
	return (0);
}

void	parse_end(t_shell *shell)
{
	if (shell->parse_fail_L != 0)
	{
		write(2, "Parse fail\n", 11);
		shell->exit_code = shell->parse_fail_L;
		shell->parse_fail_L = 0;
	}
	else
	{
		execution(shell, shell->environment);
		if (shell->pipe_split_L)
			shell->pipe_split_L = free_array(shell->pipe_split_L);
		shell->environment->export_env = remake_env(shell->environment);
		shell->environment->path = remake_path(shell->environment);
	}
}

bool	syntax_check(t_shell *shell)
{
	shell->input_L = ft_strtrim_free(shell->input_L, " ");
	if (!shell->input_L || shell->input_L[0] == '\0')
		return (FALSE);
	else if (open_quote_or_no(shell->input_L) == 1)
		return (FALSE);
	else if (check_pipes(shell->input_L) == 1)
		return (FALSE);
	else if (operator_valid(shell->input_L) == FALSE)
		return (FALSE);
	return (TRUE);
}
