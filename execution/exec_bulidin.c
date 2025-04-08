/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bulidin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:09:53 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/06 21:18:27 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
	{
		return (1);
	}
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
		{
			i++;
		}
		else
		{
			return (1);
		}
	}
	return (0);
}

int	exec_bulidin( t_shell *shell, t_context *cntx, t_environment *env)
{
	char	*path;

	if (ft_strcmp(cntx->args[0], "echo") == 0)
		return (my_echo(cntx));
	else if (ft_strcmp(cntx->args[0], "cd") == 0)
	{
		path = NULL;
		if (cntx->args && cntx->args[1])
			path = cntx->args[1];
		return (my_cd(env, path));
	}
	else if (ft_strcmp(cntx->args[0], "pwd") == 0)
		return (ms_pwd(cntx));
	else if (ft_strcmp(cntx->args[0], "export") == 0)
		return (ft_export(cntx, env->vals, shell));
	else if (ft_strcmp(cntx->args[0], "unset") == 0)
		return (my_unset(&env->vals, cntx->args[1]));
	else if (ft_strcmp(cntx->args[0], "ENV") == 0 || \
		ft_strcmp(cntx->args[0], "env") == 0)
		return (ft_env(env->vals, cntx));
	else if (ft_strcmp(cntx->args[0], "exit") == 0)
		ft_exit(shell, cntx);
	return (1);
}

bool	is_bulidin(char *str)
{
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, "echo") == 0)
		return (true);
	else if (ft_strcmp(str, "cd") == 0)
		return (true);
	else if (ft_strcmp(str, "pwd") == 0)
		return (true);
	else if (ft_strcmp(str, "export") == 0)
		return (true);
	else if (ft_strcmp(str, "unset") == 0)
		return (true);
	else if (ft_strcmp(str, "env") == 0 || ft_strcmp(str, "ENV") == 0)
		return (true);
	else if (ft_strcmp(str, "exit") == 0)
		return (true);
	return (false);
}

bool	run_bulidin( t_shell *shell, t_context *context, t_environment *env)
{
	if (exec_bulidin(shell, context, env) != 0)
		return (false);
	return (true);
}
