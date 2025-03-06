/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:33:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 03:06:43 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int flag)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (flag == 1)
		free (s1);
	if (flag == 2)
		free (s2);
	if (flag == 3)
	{
		free(s1);
		free(s2);
	}
	return (str);
}
