/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:21:30 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 02:56:51 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**free_array(char **result)
{
	int	i;

	i = 0;
	if (!result)
		return (NULL);
	while (result && result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

int	make_words(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!*s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
			i = skip_quotes(s, i);
		if (s[i] == '\0')
			break ;
		if (s[i] == c)
			count++;
		i++;
	}
	count++;
	return (count);
}

char	**make_letters(char **result, char const *s, char c, int count)
{
	int	i;
	int	counter;
	int	len;

	i = 0;
	counter = 0;
	len = 0;
	while (s[i] != '\0' && counter < count)
	{
		if (s[i] == '"' || s[i] == '\'')
			i = skip_quotes(s, i);
		while (s[i] == ' ' && s[i] != '\0')
			i++;
		if (s[i] != c)
		{
			while (s[i + len] != '\0' && s[i + len] != c)
			{
				if (s[i + len] == '"' || s[i + len] == '\'')
					len = skip_quotes(s, (i + len)) - i;
				else
					len++;
			}
			while (s[i + len - 1] != c && s[i + len - 1] == ' ')
				len--;
			result[counter] = ft_substr(s, i, len);
			if (!result[counter])
				return (free_array(result));
			i += len;
			len = 0;
			counter++;
		}
		else
			i++;
	}
	result[counter] = NULL;
	return (result);
}

char	**one_word(char const *s, char **result)
{
	result[0] = ft_strdup(s);
	result[1] = NULL;
	return (result);
}

char	**split_pipes(char const *s, char c)
{
	char	**result;
	int		count;

	count = make_words(s, c);
	result = ft_calloc(sizeof(char *), (count + 1));
	if (!result)
		return (NULL);
	if (count == 1)
		return (one_word(s, result));
	return (make_letters(result, s, c, count));
}
