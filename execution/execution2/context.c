/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:00:06 by amagoury          #+#    #+#             */
/*   Updated: 2025/03/05 23:01:44 by amagoury         ###   ########.fr       */
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
	// TODO handle failure
	handle_everything(context,cmd, env->export_env);
	return context;
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
			// TODO FREE SHELL ENV AND WHATEVER U NEED
			free_context_list(context);
			exit(status);
		}
		temp = context->next;
		free_context(context);
		context = temp;
	}
	return (pid);
}