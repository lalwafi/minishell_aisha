/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:51:06 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/11 11:45:46 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*sr;
	size_t	i;

	i = 0;
	sr = (char *)s;
	while (i < n)
	{
		if ((unsigned char) sr[i] == (unsigned char)c)
			return (&sr[i]);
		i++;
	}
	return (NULL);
}
