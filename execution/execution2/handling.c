/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:04:46 by amagoury          #+#    #+#             */
/*   Updated: 2025/03/06 15:43:24 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input(t_context *context, char *file, bool ignore)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(file, 2);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", 2);
		else
			ft_putstr_fd(": No such file or directory\n", 2);
		context->error = 1;
		return ;
	}
	if (ignore)
	{
		close(fd);
		return ;
	}
	safe_close(context->inputfd);
	context->inputfd = fd;
}

void	handle_output(t_context *context, char *file, bool append)
{
	safe_close(context->outputfd);
	if (append)
		context->outputfd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		context->outputfd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (context->outputfd == -1)
	{
		ft_putstr_fd(file, 2);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", 2);
		else
			ft_putstr_fd(": No such file or directory\n", 2);
		context->error = 1;
		return ;
	}
}

void	handle_redirects(t_context *context, t_command *command)
{
	t_direct	*temp;

	temp = command->redir;
	while (temp && context->error == 0)
	{
		if (temp->direct == RE_INPUT)
			handle_input(context, temp->file, find_heredoc_after(temp));
		if (temp->direct == RE_OUTPUT)
			handle_output(context, temp->file, false);
		if (temp->direct == APPEND)
			handle_output(context, temp->file, true);
		temp = temp->next;
	}
}
