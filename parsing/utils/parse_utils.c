/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:17:23 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 16:31:44 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(char *str)
{
	int	i;
	int	pipes;

	i = -1;
	pipes = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			pipes++;
	}
	return (pipes);
}

int	skip_quotes(const char *str, int i)
{
	char	quote;

	if (str[i] == '"' || str[i] == '\'')
	{
		quote = str[i];
		i++;
		while (str[i] != '\0' && str[i] != quote)
			i++;
		if (str[i] == quote)
			i++;
	}
	return (i);
}

int	open_quote_or_no(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i] != '\0')
				i++;
			if (str[i] != '"')
				return (1);
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (str[i] != '\'')
				return (1);
		}
	}
	return (0);
}
