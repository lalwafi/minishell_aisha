/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:05:44 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/11 11:51:57 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int c, size_t len)
{
	size_t	i;
	char	*ap;

	ap = (char *)p;
	i = 0;
	while (i < len)
	{
		ap[i] = c;
		i++;
	}
	return ((void *) ap);
}
