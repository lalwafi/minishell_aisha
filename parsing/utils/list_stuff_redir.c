/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stuff_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:25:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 03:05:39 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_redir(t_direct *lst)
{
	t_direct	*current;
	int			count;

	count = 0;
	if (!lst)
		return (0);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}

t_direct	*ft_lstlast_redir(t_direct *lst)
{
	t_direct	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_lstadd_back_redir(t_direct **lst, t_direct *new)
{
	t_direct	*last;

	if (*lst)
	{
		last = ft_lstlast_redir(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void	ft_lstclear_redir(t_direct *lst)
{
	t_direct	*a;

	while (lst)
	{
		a = lst->next;
		free(lst->file);
		free(lst);
		lst = a;
	}
}
