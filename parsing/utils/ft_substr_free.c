/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:12:56 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 03:07:13 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char	*str;

	str = ft_substr(s, start, len);
	free (s);
	return (str);
}
