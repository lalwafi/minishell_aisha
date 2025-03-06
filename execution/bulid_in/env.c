/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:37:59 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/05 13:35:04 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_values *env, t_context *context)
{
	int	fd;

	fd = context->outputfd;
	if (fd == -1)
		fd = 1;
	if (!env)
		return (1);
	while (env)
	{
		ft_putstr_fd(env->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(env->value, fd);
		write(fd, "\n", 1);
		env = env->next;
	}
	return (0);
}
