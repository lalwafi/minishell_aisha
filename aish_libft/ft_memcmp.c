/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:08:37 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/11 11:47:25 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*j;
	int				i;

	i = 0;
	a = (unsigned char *)s1 ;
	j = (unsigned char *)s2 ;
	while (n > 0)
	{
		if (a[i] != j[i])
		{
			return (a[i] - j[i]);
		}
		i++;
		n--;
	}
	return (0);
}
