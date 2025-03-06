/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:16:42 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 02:47:00 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipes(char *input)
{
	int	i;
	int	j;

	i = -1;
	j = ft_strlen(input) - 1;
	if (input[0] == '|' || input[j] == '|')
		return (1);
	while (input[++i])
	{
		if (input[i] == '|' && input[i + 1] != '\0')
		{
			while (input[++i] && input[i] != ' ')
				;
			if (input[i] == '|')
				return (1);
			else if (input[i] == '\0' || input[i + 1] == '\0')
				return (0);
		}
	}
	return (0);
}

bool	operator_valid(char *input)
{
	int		i;
	char	*cmp;

	cmp = " <>|";
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_quotes(input, i);
		else if (input[i] == '<' || input[i] == '>')
		{
			if ((input[i] == '<' && input[i + 1] == '<') || \
				(input[i] == '>' && input[i + 1] == '>'))
				i += 2;
			else
				i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (input[i] == '\0' || ft_strchr(cmp, input[i]) != NULL)
				return (FALSE);
		}
		else
			i++;
	}
	return (TRUE);
}
