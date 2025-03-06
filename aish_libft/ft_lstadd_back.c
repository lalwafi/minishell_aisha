/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:07:40 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/11 10:59:24 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *to_add)
{
	t_list	*n_last;

	if (!lst || !to_add)
		return ;
	n_last = ft_lstlast(*lst);
	if (n_last)
		n_last->next = to_add;
	else
		*lst = to_add;
}
