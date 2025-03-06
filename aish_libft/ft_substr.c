/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:22:57 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/11 12:34:55 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	a_len;

	if (!s)
		return (NULL);
	a_len = ft_strlen(s);
	if (len == 0 || start >= a_len)
		return (ft_strdup(""));
	if (len > a_len - start)
		len = a_len - start;
	str = malloc (sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy (str, s + start, len + 1);
	return (str);
}
