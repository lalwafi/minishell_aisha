/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:45:26 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/06 21:30:09 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(t_values *env, bool export, int fd) //
{
	char	*quoted_value;

	(void) export;
	if (!env)
		return ;
	while (env)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env->key, fd);
		ft_putstr_fd("=", fd);
		quoted_value = add_quotes(env->value);
		ft_putendl_fd(quoted_value, fd);
		free(quoted_value);
		env = env->next;
	}
}

int	env_add(char *value, char ***env)
{
	char	**new_env;
	int		i;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (0);
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = ft_strdup((*env)[i]);
		if (!new_env[i])
			return (0);
		i++;
	}
	new_env[i] = ft_strdup(value);
	new_env[i + 1] = NULL;
	*env = new_env;
	return (1);
}

char	*value_time(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	i++;
	while (str[i + j])
		j++;
	value = ft_calloc(sizeof(char), (j + 1));
	j = 0;
	while (str[i + j])
	{
		value[j] = str[j + i];
		j++;
	}
	return (value);
}

void	add_to_env_export(char *new, t_values *vals, t_shell *shell, \
t_context *cntx)
{
	t_values	*temp;

	temp = malloc(sizeof(t_values));
	if (!temp)
		(write(2, "malloc fail\n", 12), free_all(shell), \
		free_context_list(cntx), exit(EXIT_FAILURE));
	temp->key = key_time(new);
	temp->value = value_time(new);
	temp->next = NULL;
	ft_lstadd_back_values(&vals, temp);
}

bool	ft_export(t_context *cntx, t_values *env, t_shell *shell)
{
	int	i;
	int	fd;

	fd = cntx->outputfd;
	if (fd == -1)
		fd = 1;
	if (!cntx->args[1])
	{
		print_env(env, true, fd);
		return (true);
	}
	i = 0;
	while (cntx->args[++i])
	{
		if (!is_valid_env(cntx->args[i]))
			return (ft_putstr_fd("not a valid identifier\n", 2), false);
		else
			add_to_env_export(cntx->args[i], env, shell, cntx);
	}
	return (true);
}
