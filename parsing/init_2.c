/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:51:53 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 12:27:37 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell(t_shell *shell)
{
	shell->pipe_split_L = NULL;
	shell->input_L = NULL;
	shell->exit_code = 0;
	shell->parse_fail_L = 0;
}

t_command	*initialize_commands(void)
{
	t_command	*cmd;

	cmd = ft_calloc(sizeof(t_command), 1);
	if (!cmd)
		(write(2, "\033[0;31mError: command malloc fail\033[0m\n", 36),
			exit(EXIT_FAILURE));
	cmd->cmd_args = NULL;
	cmd->cmd_line_L = NULL;
	cmd->words_L = NULL;
	cmd->num_of_redir = 0;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}
