/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:17:27 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/11 11:50:56 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst1;
	const unsigned char	*src1;

	dst1 = (unsigned char *) dst;
	src1 = (const unsigned char *) src;
	if (!dst && !src)
		return (NULL);
	if (dst1 < src1)
	{
		while (len--)
			*dst1++ = *src1++;
	}
	else if (dst1 > src1)
	{
		dst1 = dst1 + len;
		src1 = src1 + len;
		while (len--)
		{
			*(--dst1) = *(--src1);
		}
	}
	return (dst);
}
