/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 20:48:03 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/06 17:02:22 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*delete_quotes(char *str, int j, char *result, char quote)
{
	bool	in_q;
	int		i;

	i = 0;
	in_q = FALSE;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && in_q == FALSE)
		{
			quote = str[i];
			in_q = TRUE;
			i++;
		}
		else if ((str[i] == '\'' || str[i] == '\"') && \
			in_q == TRUE && quote == str[i])
		{
			in_q = FALSE;
			i++;
		}
		else if (str[i] && (in_q != TRUE || str[i] != quote))
			result[j++] = str[i++];
	}
	result[j] = '\0';
	free(str);
	return (result);
}

char	*rmv_quotes(char *str)
{
	char	quote;
	char	*result;
	int		len;

	quote = '\0';
	len = count_rmv_quotes(str, 0, 0);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	return (delete_quotes(str, 0, result, quote));
}

int	count_rmv_quotes(char *str, int i, int len)
{
	bool	in_q;
	char	quote;

	in_q = false;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && in_q == false)
		{
			quote = str[i];
			in_q = true;
			i++;
		}
		else if ((str[i] == '\'' || str[i] == '\"') && \
			in_q == TRUE && quote == str[i])
			in_q = FALSE;
		if (str[i] && (in_q == FALSE || str[i] != quote))
		{
			len++;
			i++;
		}
	}
	return (len);
}

// int	main(void)
// {
// 	char	*a = "echo \"hello\"'' meow";
// 	char	*b;

// 	b = rmv_quotes(a);
// 	printf("a = #%s#\nb = #%s#\n", a, b);
// }

// he"ll'o world"
// echo "hello"'' meow