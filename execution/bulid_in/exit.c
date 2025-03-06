/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:45:07 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/06 02:11:38 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_shell(t_shell *shell, t_context *text)
{
	// int	exit_code;

	// exit_code = shell->exit_code;
	free_all(shell);
	free_context_list(text);
	exit(shell->exit_code);
}
