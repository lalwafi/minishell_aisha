/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:49:04 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 02:46:07 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	operator_tokens(t_shell *shell, t_command *cmds, int i)
{
	char		*cmp;
	t_direct	*temp;
	int			start;

	cmp = " <>|";
	start = i;
	temp = malloc(sizeof(t_direct));
	if (!temp)
		(write(2, "malloc fail\n", 12), free_all(shell), exit(EXIT_FAILURE));
	temp->direct = operators_check(cmds->cmd_line_L, i);
	if (temp->direct == HERE_DOC || temp->direct == APPEND)
		i += 2;
	else if (temp->direct == RE_INPUT || temp->direct == RE_OUTPUT)
		i++;
	while (cmds->cmd_line_L[i] == ' ')
		i++;
	if (ft_strchr(cmp, cmds->cmd_line_L[i]) != NULL)
		shell->parse_fail_L = 1;
	temp->file = copy_file(cmds->cmd_line_L, i, cmds, start);
	if (temp->file == NULL)
		shell->parse_fail_L = 1;
	cmds->num_of_redir += 1;
	temp->next = NULL;
	ft_lstadd_back_redir(&cmds->redir, temp);
}

char	*copy_file(char *str, int i, t_command *cmds, int start)
{
	int		len;
	char	*result;
	char	*cmp;

	len = 0;
	cmp = " <>|";
	while (str[i + len] != '\0' && ft_strchr(cmp, str[i + len]) == NULL)
	{
		if (str[i + len] == '\'' || str[i + len] == '\"')
			len = skip_quotes(str, i + len) - i;
		else
			len++;
	}
	if (len == 0)
		return (NULL);
	result = rmv_quotes(ft_substr(str, i, len));
	cmds->cmd_line_L = string_but_string(cmds->cmd_line_L, \
				ft_strdup(""), start, len + i - start);
	return (result);
}

t_state	operators_check(char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		return (HERE_DOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '<' && str[i + 1] != '<')
		return (RE_INPUT);
	else
		return (RE_OUTPUT);
}
