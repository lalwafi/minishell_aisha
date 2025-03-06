/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:21:30 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 17:13:52 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	t_split	*split;

	split = ft_calloc(sizeof(t_split), 1);
	split->i = 0;
	split->counter = 0;
	split->len = 0;
	split->result = result;
	while (s[split->i] != '\0' && split->counter < count)
	{
		if (s[split->i] == '"' || s[split->i] == '\'')
			split->i = skip_quotes(s, split->i);
		while (s[split->i] == ' ' && s[split->i] != '\0')
			split->i++;
		if (s[split->i] != c)
		{
			split = make_letters_2(split, s, c);
			if (split == NULL)
				return (NULL);
		}
		else
			split->i++;
	}
	result[split->counter] = NULL;
	return (result);
}

t_split	*make_letters_2(t_split *sp, char const *s, char c)
{
	while (s[sp->i + sp->len] != '\0' && s[sp->i + sp->len] != c)
	{
		if (s[sp->i + sp->len] == '"' || s[sp->i + sp->len] == '\'')
			sp->len = skip_quotes(s, (sp->i + sp->len)) - sp->i;
		else
			sp->len++;
	}
	while (s[sp->i + sp->len - 1] != c && s[sp->i + sp->len - 1] == ' ')
		sp->len--;
	sp->result[sp->counter] = ft_substr(s, sp->i, sp->len);
	if (!sp->result[sp->counter])
		return (NULL);
	sp->i += sp->len;
	sp->len = 0;
	sp->counter++;
	return (sp);
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
