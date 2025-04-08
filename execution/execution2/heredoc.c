/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:33:58 by amagoury          #+#    #+#             */
/*   Updated: 2025/03/07 02:31:20 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal(int signum)
{
	if (signum == SIGINT)
	{
		close(0);
		g_sig = signum;
	}
}

int	heredoc_child(int fds[2], char *delim, t_shell *shell)
{
	char	*str;

	signal(SIGINT, heredoc_signal);
	close(fds[0]);
	str = readline("heredoc> ");
	while (str && ft_strncmp(str, delim, -1) != 0)
	{
		str = expand_them_vars(str, shell);
		ft_putendl_fd(str, fds[1]);
		free(str);
		str = readline("heredoc> ");
	}
	close(fds[1]);
	if (g_sig != 0)
		return (1);
	return (0);
}

bool	handle_heredoc(t_context *context, char *delim, t_shell *shell)
{
	int	fds[2];
	int	pid;
	int	status;

	if (pipe(fds) == -1)
		return (false);
	pipe(fds);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fds[0]);
		close(fds[1]);
		return (false);
	}
	if (pid == 0)
		exit(heredoc_child(fds, delim, shell));
	close(fds[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
		return (close(fds[0]), false);
	safe_close(context->inputfd);
	context->inputfd = fds[0];
	return (true);
}

bool	find_heredoc_after(t_direct *direct)
{
	while (direct)
	{
		if (direct->direct == HERE_DOC)
			return (true);
		direct = direct->next;
	}
	return (false);
}

t_context	*handle_heredocs(t_command *command, int inputfd, t_shell *shell)
{
	t_direct	*temp;
	t_context	*context;
	int			fds[2];

	context = create_context();
	context->inputfd = inputfd;
	temp = command->redir;
	while (temp)
	{
		if (temp->direct == HERE_DOC)
		{
			if (handle_heredoc(context, temp->file, shell) == FALSE)
				shell->exit_code = 1;
		}
		temp = temp->next;
	}
	if (command->next)
	{
		pipe(fds);
		context->next = handle_heredocs(command->next, fds[0], shell);
		if (context->next == NULL)
			return (close(fds[0]), close(fds[1]), free_context(context), NULL);
		context->outputfd = fds[1];
	}
	return (context);
}
