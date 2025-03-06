/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:15:38 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/05 21:24:38 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_name(char *dest, const char *src)
{
	int	i;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && src[i] != '=' && i < BUFF_SIZE - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

bool	is_valid_env(const char *env_var)
{
	int	i;

	i = 0;
	if (!*env_var)
		return (false);
	if (!ft_isalpha(env_var[0]) && env_var[0] != '_')
		return (false);
	while (env_var[i] && env_var[i] != '=')
	{
		if (!ft_isalnum(env_var[i]) && env_var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
