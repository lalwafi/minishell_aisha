/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:30:43 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 19:54:37 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_loop(t_shell *shell, t_command **ctemp, int i)
{
	while ((*ctemp)->cmd_line_L[i])
	{
		if ((*ctemp)->cmd_line_L[i] == '\"' || \
			(*ctemp)->cmd_line_L[i] == '\'')
			i = token_quotes(ctemp, i);
		else if ((*ctemp)->cmd_line_L[i] == '>' || \
			(*ctemp)->cmd_line_L[i] == '<')
		{
			operator_tokens(shell, (*ctemp), i);
			i = 0;
		}
		else if (i > 0 && ((*ctemp)->cmd_line_L[i] == ' ' || \
			(*ctemp)->cmd_line_L[i] == '\0' || \
			(*ctemp)->cmd_line_L[i + 1] == '\0'))
		{
			(*ctemp)->words_L = ft_strjoin_free((*ctemp)->words_L, \
				ft_substr((*ctemp)->cmd_line_L, 0, i + 1), 3);
			(*ctemp)->cmd_line_L = ft_substr_free((*ctemp)->cmd_line_L, i + 1, \
				ft_strlen((*ctemp)->cmd_line_L + 2));
			i = 0;
		}
		else
			i++;
	}
	return (i);
}

int	token_quotes(t_command **ctemp, int i)
{
	i = skip_quotes((*ctemp)->cmd_line_L, i);
	if ((*ctemp)->cmd_line_L[i] == '\0')
	{
		(*ctemp)->words_L = ft_strjoin_free((*ctemp)->words_L, \
			ft_substr((*ctemp)->cmd_line_L, 0, i), 3);
		(*ctemp)->cmd_line_L = ft_substr_free((*ctemp)->cmd_line_L, i, \
			ft_strlen((*ctemp)->cmd_line_L + 2));
		i = 0;
	}
	return (i);
}
