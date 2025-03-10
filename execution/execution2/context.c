/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:00:06 by amagoury          #+#    #+#             */
/*   Updated: 2025/03/06 16:26:03 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_context(t_context *context)
{
	free(context->cmd);
	free_array(context->args);
	safe_close(context->inputfd);
	safe_close(context->outputfd);
	free(context);
}

t_context	*create_context_list(t_command *cmd, \
t_environment *env, t_shell *shell)
{
	t_context	*context;

	context = handle_heredocs(cmd, -1, shell);
	if (!context)
	{
		write(2, "Error: Failed to handle heredocs\n", 33);
		return (NULL);
	}
	handle_everything(context, cmd, env->export_env);
	return (context);
}

void	free_context_list(t_context *context)
{
	t_context	*temp;

	while (context)
	{
		temp = context->next;
		free_context(context);
		context = temp;
	}
}

int	execute_context(t_shell *shell, t_context *context, t_environment *env)
{
	int			pid;
	t_context	*temp;
	int			status;

	while (context)
	{
		pid = fork();
		if (pid == 0)
		{
			status = execute_command(shell, context, env);
			free_all(shell);
			free_context_list(context);
			exit(status);
		}
		temp = context->next;
		free_context(context);
		context = temp;
	}
	return (pid);
}
