/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stuff_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:25:27 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 03:07:01 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_cmds(t_command *lst)
{
	t_command	*current;
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

t_command	*ft_lstlast_cmds(t_command *lst)
{
	t_command	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_lstadd_back_cmds(t_command **lst, t_command *new)
{
	t_command	*last;

	if (*lst)
	{
		last = ft_lstlast_cmds(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
