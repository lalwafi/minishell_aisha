/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:17:44 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/06 21:30:16 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ms_pwd(t_context *context)
{
	char	*cwd;
	int		fd;

	fd = context->outputfd;
	if (fd == -1)
		fd = 1;
	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, fd);
	free(cwd);
	return (0);
}
