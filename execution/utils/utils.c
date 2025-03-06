/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:50:30 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/06 15:44:01 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_strjoin_free_a(char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char	*add_quotes(char *value)
{
	char	*equal_sign;
	char	*new_value;

	equal_sign = ft_strchr(value, '=');
	if (!equal_sign)
		return (ft_strdup(value));
	if (*(equal_sign + 1) == '\"')
		return (ft_strdup(value));
	new_value = ft_strjoin_free_a(ft_strdup(value), "\"");
	new_value = ft_strjoin_free_a(new_value, equal_sign + 1);
	new_value = ft_strjoin_free_a(new_value, "\"");
	return (new_value);
}

t_context	*create_context(void)
{
	t_context	*context;

	context = malloc(sizeof(t_context));
	if (!context)
		return (NULL);
	context->args = NULL;
	context->cmd = NULL;
	context->inputfd = -1;
	context->outputfd = -1;
	context->error = 0;
	context->next = NULL;
	return (context);
}

void	safe_close(int fd)
{
	if (fd != -1)
		close(fd);
}
