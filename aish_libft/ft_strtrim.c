/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:54:04 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/11 12:27:03 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	setchr(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	a;
	size_t	s_len;
	char	*str;

	if (!s1)
		return (NULL);
	else if (!set)
		set = "";
	i = 0;
	a = ft_strlen(s1) - 1;
	while (s1[i] && setchr(s1[i], set))
		i++;
	while (a >= i && setchr(s1[a], set))
		a--;
	s_len = a - i + 1;
	if (s_len <= 0)
		s_len = 0;
	str = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + i, s_len + 1);
	return (str);
}
