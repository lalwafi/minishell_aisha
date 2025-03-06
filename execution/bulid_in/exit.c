/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:45:07 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/06 18:10:34 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_utils(t_shell *shell, t_context *cntx)
{
	if (ft_str_isnum(cntx->args[1]) != 0)
		exit_utils2(shell, cntx->args[1], cntx);
	else
	{
		shell->exit_code = 1;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	}
}

void	exit_utils2(t_shell *shell, char *arg, t_context *cntx)
{
	shell->exit_code = 255;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free_exit(shell, cntx);
}

void	free_exit(t_shell *shell, t_context *cntx)
{
	int	i;

	i = shell->exit_code;
	free_all(shell);
	free_context_list(cntx);
	exit(i);
}

int	ft_str_isnum(char *c)
{
	int	i;

	i = 0;
	if (c[i] == '+' || c[i] == '-')
		i++;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			return (1);
		++i;
	}
	return (0);
}

int	ft_exit(t_shell *shell, t_context *cntx)
{
	int	arg_count;

	arg_count = 0;
	while (cntx->args[arg_count])
		arg_count++;
	if (arg_count > 2)
		exit_utils(shell, cntx);
	else if (arg_count == 2)
	{
		if (ft_str_isnum(cntx->args[1]) == 0)
		{
			shell->exit_code = ft_atoi(cntx->args[1]);
			free_exit(shell, cntx);
		}
		else
			exit_utils2(shell, cntx->args[1], cntx);
	}
	else
	{
		free_exit(shell, cntx);
	}
	return (1);
}
