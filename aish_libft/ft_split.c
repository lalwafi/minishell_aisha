/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:45:49 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/11 12:02:17 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *a, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (a[i])
	{
		if (a[i] && a[i] != c)
		{
			w++;
			while (a[i] && a[i] != c)
				i++;
		}
		else
			i++;
	}
	return (w);
}

static int	handle_word(char	**split, char *w, int y)
{
	size_t	i;

	if (!w)
	{
		i = 0;
		while (i < (size_t)y)
		{
			free(split[i]);
			i++;
		}
		free(split);
		return (0);
	}
	split[y] = w;
	return (1);
}

static char	**handle_split(char	**split, char const *a, char c)
{
	int	i;
	int	y;
	int	str;

	i = 0;
	y = 0;
	while (a[i])
	{
		if (a[i] && a[i] != c)
		{
			str = i;
			while (a[i] && a[i] != c)
				i++;
			if (!handle_word(split, ft_substr(a, str, i - str), y))
				return (NULL);
			y++;
		}
		else
			i++;
	}
	split[y] = NULL;
	return (split);
}

char	**ft_split(char const *a, char c)
{
	char	**split;
	size_t	s_len;

	if (!a)
		return (NULL);
	s_len = count_word(a, c) + 1;
	split = malloc((sizeof(char *) * s_len));
	if (!split)
		return (NULL);
	return (handle_split(split, a, c));
}
