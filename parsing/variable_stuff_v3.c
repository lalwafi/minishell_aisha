/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_stuff_v3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:04:17 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 20:08:02 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo $USER $SHLVL $? $$USER $USERRR

char	*expand_them_vars(char *str, t_shell *shell)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		printf("1 i = %d\n", i);
		if (str[i] == '\'')
			i = skip_quotes(str, i) - 1;
		else if (str[i] == '$')
		{
			if (str[i + 1] == '\0')
				break ;
			printf("2 i = %d\n", i);
			str = expand_word_vars(str, i + 1, shell);
			printf("3 i = %d\n", i);
			i--;
		}
	}
	return (str);
}

char	*string_but_string(char *pushed, char *pusher, int start, int rmv)
{
	char	*result;

	result = string_but_string_2(pushed, pusher, start, rmv);
	if (pushed)
		free(pushed);
	if (pusher)
		free(pusher);
	return (result);
}

char	*string_but_string_2(char *pushed, char *pusher, int start, int rmv)
{
	int		i;
	int		j;
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(pushed) + \
			ft_strlen(pusher) - rmv + 1));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (pushed[++i])
	{
		if (i == start)
		{
			i += rmv - 1;
			rmv = -1;
			while (pusher[++rmv])
				result[j++] = pusher[rmv];
		}
		else
			result[j++] = pushed[i];
	}
	result[j] = '\0';
	return (result);
}

char	*return_var(char *str, int start, int len, t_environment *env)
{
	t_values	*temp;
	char		*var;

	var = ft_substr(str, start, len);
	if (!var)
		return (ft_strdup(""));
	temp = env->vals;
	while (temp)
	{
		if (ft_strcmp_l(temp->key, var) == 0)
			return (free(var), ft_strdup(temp->value));
		temp = temp->next;
	}
	free(var);
	return (ft_strdup(""));
}

char	*expand_word_vars(char *str, int i, t_shell *sh)
{
	int		len;
	char	*var;

	len = 1;
	printf("4 i = %d\n", i);
	if (str[i] == '?')
		var = ft_itoa(sh->exit_code);
	else if (ft_isdigit(str[i]) == 1)
		var = return_var(str, i, 1, sh->environment);
	else if (ft_isalpha(str[i]) || str[i] == '_')
	{
		printf("5 i = %d\n", i);
		len = 0;
		while (str[i + len] != '\0' && \
			(ft_isalpha(str[i + len]) == 1 || \
			str[i + len] == '_' || ft_isdigit(str[i + len]) == 1))
			len++;
		printf("6 i = %d\n", i);
		var = return_var(str, i, len, sh->environment);
		printf("7 i = %d\n", i);
	}
	else
		len = 0;
	if (len > 0)
	{
		printf("8 i = %d\n", i);
		str = string_but_string(str, var, --i, len + 1);
		printf("9 i = %d\n", i);
		if (str == NULL)
			(write(2, "malloc fail\n", 12), \
			free_all(sh), exit(EXIT_FAILURE));
	}
	printf("10 i = %d\n", i);
	return (str);
}
