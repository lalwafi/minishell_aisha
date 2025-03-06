/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:56:21 by aishamagour       #+#    #+#             */
/*   Updated: 2025/03/06 13:19:49 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenize_it(t_shell *shell, char *str, int i)
{
	char		*cut;
	t_command	*ctemp;

	ctemp = initialize_commands();
	ctemp->cmd_line_L = ft_strdup(str);
	ctemp->words_L = ft_strdup("");
	if (!ctemp->cmd_line_L)
		(free_all(shell), \
		write(2, "Error: malloc fail\n", 19), exit(EXIT_FAILURE));
	i = tokenize_loop(shell, &ctemp, i);
	if (ctemp->cmd_line_L[i] == '\0' && i > 0)
	{
		ctemp->words_L = ft_strjoin_free(ctemp->words_L, \
			ft_substr(ctemp->cmd_line_L, 0, i), 3);
		ctemp->cmd_line_L = ft_substr_free(ctemp->cmd_line_L, i, \
			ft_strlen(ctemp->cmd_line_L + 1));
	}
	cut = ft_strtrim_free(rmv_extra_spaces(ctemp->words_L), " ");
	ctemp->cmd_args = split_pipes(cut, ' ');
	free(cut);
	ctemp->next = NULL;
	i = -1;
	while (ctemp->cmd_args[++i])
		ctemp->cmd_args[i] = rmv_quotes(ctemp->cmd_args[i]);
	ft_lstadd_back_cmds(&shell->commands, ctemp);
	print_commands(shell->commands);
}

void	print_commands(t_command *cmds)
{
	t_command	*ctemp;
	t_direct	*temp;
	int			i;

	ctemp = cmds;
	i = 0;
	while (ctemp)
	{
		printf("----- commands %i -----\n", i++);
		if (ctemp->cmd_line_L)
			printf("cmd_line = #%s#\n", ctemp->cmd_line_L);
		if (ctemp->cmd_args)
		{
			i = -1;
			while (ctemp->cmd_args[++i])
				printf("cmd_args[%d] = #%s#\n", i, ctemp->cmd_args[i]);
		}
		printf("num_of_redir = %d\n", ctemp->num_of_redir);
		temp = ctemp->redir;
		while (temp)
		{
			print_enum(temp->direct);
			printf(" , file =  #%s#\n", temp->file);
			temp = temp->next;
		}
		ctemp = ctemp->next;
	}
	printf("-----------------------\n");
}

void	print_enum(t_state en)
{
	if (en == RE_INPUT)
		printf("redirect = <");
	else if (en == RE_OUTPUT)
		printf("redirect = >");
	else if (en == HERE_DOC)
		printf("redirect = <<");
	else if (en == APPEND)
		printf("redirect = >>");
}
