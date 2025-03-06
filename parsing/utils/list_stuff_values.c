/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stuff_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:29:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 03:06:09 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	values_size(t_values *vals)
{
	t_values	*temp;
	int			i;

	i = 0;
	temp = vals;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

t_values	*ft_lstlast_values(t_values *lst)
{
	t_values	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_lstadd_back_values(t_values **lst, t_values *new)
{
	t_values	*last;

	if (*lst)
	{
		last = ft_lstlast_values(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void	ft_lstclear_values(t_values *lst)
{
	t_values	*a;

	while (lst)
	{
		a = lst->next;
		free(lst->key);
		free(lst);
		lst = a;
	}
}

void	ft_lstdelone_values(t_values *prev, t_values *del, t_values *nxt)
{
	prev->next = nxt;
	if (del)
	{
		free(del->key);
		free(del);
	}
}
