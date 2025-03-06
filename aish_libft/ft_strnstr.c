/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:46:04 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/11 12:24:14 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *li, const char *ci, size_t len)
{
	size_t	i;
	size_t	a;

	i = 0;
	if (*ci == '\0')
		return ((char *) li);
	while (i < len && li[i] != '\0')
	{
		a = 0;
		while (i + a < len && li[i + a] == ci[a] && ci[a] != '\0')
			a++;
		if (ci[a] == '\0')
			return ((char *)li + i);
		i++;
	}
	return (0);
}
