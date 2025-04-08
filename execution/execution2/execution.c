/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:11:32 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 21:44:17 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_strs(char **strs)
{
	char	**new;
	int		i;

	i = 0;
	while (strs[i])
		i++;
	new = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (strs[i])
	{
		new[i] = ft_strdup(strs[i]);
		if (new[i] == NULL)
			return (free_array(new), NULL);
		i++;
	}
	return (new);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (!*env)
		return (NULL);
	paths = ft_split(*env + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin_free(ft_strjoin(paths[i], "/"), cmd, 1);
		if (!path)
			return (free_array(paths), NULL);
		if (access(path, X_OK) == 0)
			return (free_array(paths), path);
		free(path);
	}
	return (free_array(paths), NULL);
}

static void	execute_command_2(t_context *context)
{
	(dup2(context->inputfd, 0), close(context->inputfd));
	context->inputfd = -1;
}

int	execute_command( t_shell *shell, t_context *context, t_environment *env, \
	int errnum)
{
	if (context->next)
		free_context_list(context->next);
	context->next = NULL;
	if (context->error != 0)
		return (context->error);
	if (context->inputfd != -1)
		execute_command_2(context);
	if (context->outputfd != -1)
	{
		(dup2(context->outputfd, 1), close(context->outputfd));
		context->outputfd = -1;
	}
	if (context->cmd == NULL)
		return (ft_putstr_fd(context->args[0], 2),
			ft_putstr_fd(": Command not found\n", 2), 127);
	if (is_bulidin(context->cmd))
		return (run_bulidin(shell, context, env));
	execve(context->cmd, context->args, env->export_env);
	errnum = errno;
	ft_putstr_fd(context->args[0], 2);
	if (errnum == EACCES)
		return (ft_putstr_fd(": Permission Denied\n", 2), 126);
	ft_putstr_fd(": Command not found\n", 2);
	return (127);
}

void	execution(t_shell *shell, t_environment *env)
{
	t_context	*context;
	int			status;
	int			last_pid;

	context = create_context_list(shell->commands, env, shell);
	if (!context)
	{
		shell->exit_code = 1;
		return ;
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (context->next == NULL && is_bulidin(context->cmd))
	{
		shell->exit_code = exec_bulidin(shell, context, env);
		return (free_context(context));
	}
	last_pid = execute_context(shell, context, env);
	signal(SIGINT, SIG_IGN);
	waitpid(last_pid, &status, 0);
	while (wait(NULL) != -1)
		;
	shell->exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		shell->exit_code = handle_signaled(WTERMSIG(status));
}
