/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:00:46 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 12:40:30 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prep_env(t_environment **env)
{
	(*env) = malloc(sizeof(t_environment));
	if (!(*env))
		(write(2, "\033[0;31mError: environment malloc fail\033[0m\n", 36),
			exit(EXIT_FAILURE));
	(*env)->cwd = getcwd(NULL, 0);
	(*env)->owd = getcwd(NULL, 0);
	(*env)->path = NULL;
	(*env)->vals = NULL;
}

void	get_env(t_shell *shell, char **env)
{
	int		i;
	int		j;
	char	*key;

	i = -1;
	prep_env(&shell->environment);
	while (env[++i])
	{
		key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		if (!key || key == NULL)
			continue ;
		if (ft_strlen(key) == 4 && ft_strncmp_lyall(key, "PATH", 4) == 0)
			shell->environment->path = ft_split(getenv(key), ':');
		make_values_node(key, shell);
		free(key);
	}
	shell->environment->export_env = malloc(sizeof(char *) * (i + 1));
	if (!shell->environment->export_env)
		(write(2, "\033[0;31mError: environment malloc fail\033[0m\n", 36),
			exit(EXIT_FAILURE));
	i = 0;
	j = 0;
	while (env[i])
		shell->environment->export_env[j++] = ft_strdup(env[i++]);
	shell->environment->export_env[j] = NULL;
}

char	*key_time(char *env)
{
	int		i;
	char	*key;

	i = 0;
	while (env[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = -1;
	while (env[++i] != '=')
		key[i] = env[i];
	key[i] = '\0';
	return (key);
}

void	make_values_node(char *key, t_shell *shell)
{
	t_values	*temp;

	temp = malloc(sizeof(t_values));
	if (!temp)
		(write(2, "malloc fail\n", 12), free_all(shell), exit(EXIT_FAILURE));
	temp->key = ft_strdup(key);
	temp->value = getenv(temp->key);
	temp->next = NULL;
	ft_lstadd_back_values(&shell->environment->vals, temp);
}
