/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:55:26 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/10 13:16:43 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curn_node;
	t_list	*next_node;

	if (!lst || !del)
		return ;
	curn_node = *lst;
	while (curn_node)
	{
		next_node = curn_node->next;
		ft_lstdelone(curn_node, del);
		curn_node = next_node;
	}
	*lst = NULL;
}
