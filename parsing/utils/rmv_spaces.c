/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmv_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:31:50 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 17:17:04 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rmv_extra_spaces(char *str)
{
	char	*result;

	result = malloc(sizeof(char) * (count_rmv_extra_spaces(0, 0, str) + 1));
	if (!result)
		return (NULL);
	result = rmv_extra_spaces_2(result, str, 0, 0);
	free(str);
	return (result);
}

int	count_rmv_extra_spaces(int i, int j, char *str)
{
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			j += skip_quotes(str, i) - i;
			i = skip_quotes(str, i);
		}
		else if (str[i] == ' ')
		{
			j++;
			while (str[i] != '\0' && str[i] == ' ')
				i++;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

char	*rmv_extra_spaces_2(char *result, char *str, int i, int j)
{
	char	quote;

	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			result[j++] = str[i++];
			while (str[i] != '\0' && str[i] != quote)
				result[j++] = str[i++];
			if (str[i] == quote)
				result[j++] = str[i++];
		}
		else if (str[i] == ' ')
		{
			result[j++] = str[i];
			while (str[i] != '\0' && str[i] == ' ')
				i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
