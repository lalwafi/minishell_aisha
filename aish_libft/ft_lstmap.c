/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:55:35 by amagoury          #+#    #+#             */
/*   Updated: 2024/01/11 12:33:44 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*butter;
	t_list	*fly;

	if (!lst || !f)
		return (NULL);
	butter = NULL;
	while (lst)
	{
		fly = ft_lstnew((*f)(lst->content));
		if (fly == NULL)
		{
			ft_lstclear(&butter, del);
			return (NULL);
		}
		ft_lstadd_back(&butter, fly);
		lst = lst->next;
	}
	return (butter);
}
