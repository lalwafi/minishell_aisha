/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:30:37 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/06 15:41:26 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	is_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	get_fd(t_context *ctx)
{
	if (ctx->outputfd == -1)
		return (1);
	else
		return (ctx->outputfd);
}

void	print_args(int fd, char **args, int i)
{
	while (args[i])
	{
		write(fd, args[i], ft_strlen(args[i]));
		if (args[++i])
			write(fd, " ", 1);
	}
}

int	my_echo(t_context *ctx)
{
	int		i;
	bool	flag;
	int		fd;

	flag = false;
	fd = get_fd(ctx);
	i = 1;
	while (ctx->args[i] && ctx->args[i][0] == '-' &&
		ctx->args[i][1] == 'n' && is_n(ctx->args[i]) == 0)
	{
		flag = true;
		i++;
	}
	print_args(fd, ctx->args, i);
	if (!flag)
		write(fd, "\n", 1);
	return (0);
}
// int	my_echo(t_context *context)
// {
// 	int		i;
// 	int		j;
// 	bool	flag;
// 	int		fd;

// 	flag = false;
// 	i = 1;
// 	fd = context->outputfd;
// 	if (fd == -1)
// 		fd = 1;
// 	while (context->args[i] && context->args[i][0] == '-' &&
// 			context->args[i][1] == 'n' && is_n(context->args[i]) == 0)
// 	{
// 		flag = true;
// 		i++;
// 	}
// 	while (context->args[i])
// 	{
// 		j = 0;
// 		while (context->args[i][j])
// 		{
// 			write(fd, &context->args[i][j], 1);
// 			j++;
// 		}
// 		if (context->args[i + 1])
// 			write(fd, " ", 1);
// 		i++;
// 	}
// 	if (flag == false)
// 		write(fd, "\n", 1);
// 	return (0);
// }
