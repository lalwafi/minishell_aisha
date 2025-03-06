/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:23:21 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 02:42:55 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remake_env(t_environment *env)
{
	int			i;
	char		**new_env;
	t_values	*temp;

	i = values_size(env->vals);
	new_env = ft_calloc(sizeof(char *), i + 1);
	if (!new_env)
		return (NULL);
	i = 0;
	temp = env->vals;
	while (temp)
	{
		new_env[i++] = ft_strjoin_free(
				ft_strjoin_free(ft_strdup(temp->key), "=", 1),
				ft_strdup(temp->value), 3);
		temp = temp->next;
	}
	free_array(env->export_env);
	return (new_env);
}

char	**remake_path(t_environment *env)
{
	char	*path;

	path = find_value("PATH", env->vals);
	if (path == NULL)
	{
		env->path = free_array(env->path);
		return (NULL);
	}
	env->path = free_array(env->path);
	return (ft_split(path, ':'));
}

char	*find_value(char *key, t_values *env)
{
	while (env)
	{
		if (ft_strcmp_l(key, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
