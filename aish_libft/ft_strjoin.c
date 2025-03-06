/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 20:08:29 by amagoury          #+#    #+#             */
/*   Updated: 2024/02/09 15:59:36 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	s_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s_len = len1 + len2;
	str = malloc(sizeof(char) * (s_len +1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy (str, s1, s_len + 1);
	ft_strlcat (str, s2, s_len + 1);
	return (str);
}
