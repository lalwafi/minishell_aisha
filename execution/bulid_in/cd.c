/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:43:01 by amagoury          #+#    #+#             */
/*   Updated: 2025/03/05 14:58:02 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_env(char *key, t_values *env)
{
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
// Search for the key in the existing environment variables
// Key found, update the value

void	set_env_var(t_environment *env, char *key, char *value)
{
	t_values	*current;
	t_values	*new_var;

	current = env->vals;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_var = (t_values *)malloc(sizeof(t_values));
	if (!new_var)
	{
		ft_putendl_fd("set_env_var: malloc failed", STDERR_FILENO);
		return ;
	}
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = env->vals;
	env->vals = new_var;
}

// Get current directory
// Handle HOME directory
// Handle previous directory
// Change directory
// Update environment variables
// Update OLDPWD
// Update PWD
// Update environment variables in the env list
// Assuming you have a function to set environment variables
int	update_env(t_environment *env, char *current_dir)
{
	if (getcwd(current_dir, PATH_MAX) == NULL)
	{
		ft_putendl_fd("cd: error updating directory", STDERR_FILENO);
		return (1);
	}
	free(env->owd);
	env->owd = ft_strdup(env->cwd);
	free(env->cwd);
	env->cwd = ft_strdup(current_dir);
	set_env_var(env, "OLDPWD", env->owd);
	set_env_var(env, "PWD", env->cwd);
	return (0);
}

char	*get_new_path(t_environment *env, char *path)
{
	if (!path || !*path)
		return (ft_get_env("HOME", env->vals));
	if (path[0] == '-' && !path[1])
	{
		ft_putendl_fd(ft_get_env("OLDPWD", env->vals), STDOUT_FILENO);
		return (ft_get_env("OLDPWD", env->vals));
	}
	return (path);
}

int	my_cd(t_environment *env, char *path)
{
	char	current_dir[PATH_MAX];
	char	*new_path;

	if (getcwd(current_dir, PATH_MAX) == NULL)
		return (ft_putendl_fd("cd: error getting current directory",
				STDERR_FILENO), 1);
	new_path = get_new_path(env, path);
	if (!new_path)
		return (ft_putendl_fd("cd: HOME or OLDPWD not set", STDERR_FILENO), 1);
	if (chdir(new_path) == -1)
		return (ft_putendl_fd("cd: no such file or directory",
				STDERR_FILENO), 1);
	return (update_env(env, current_dir));
}
