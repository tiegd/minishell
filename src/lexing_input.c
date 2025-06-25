/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:38:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/25 10:34:30 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	space_to_add(char *str)
// {
// 	int	i;
// 	int count;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '<' && str[i + 1] == '<')
// 		{
// 			i++;
// 		}
// 		else if (str[i] == '<' && exp_isalnum(str[i + 1]))
// 			count++;
// 		else if (i != 0 && str[i] == '<' && str[i + 1] != '<')
// 			count++;
// 		else if (str[i] == '>' && exp_isalnum(str[i + 1]))
// 			count++;
// 		else if (i != 0 && str[i] == '<' && str[i + 1] != '<')
// 	}
// }

int	is_append(char c, char d)
{
	if (c == '>' && d == '>')
		return (1);
	return (0);
}

int	is_here_doc(char c, char d)
{
	if (c == '<' && d == '<')
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	space_to_add(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_special(str[i]))
			count++;
		i++;
	}
	return (count);
}

char	*lexing_input(char *input)
{
	int		i;
	int		j;
	int		len;
	char	*final;

	i = 0;
	j = 0;
	len = ft_strlen(input) + space_to_add(input);
	final = ft_calloc(len, sizeof(char));
	if (!final)
		return (NULL);
	while (i < len && input[i])
	{
		if (is_special(input[i]) && !is_here_doc(input[i], input[i + 1]) 
			&& !is_append(input[i], input[i + 1]) && !is_ws(input[i + 1]))
		{
			final[j++] = input[i++];
			final[j++] = ' ';
		}
		else if (exp_isalnum(input[i]) && is_special(input[i + 1]))
		{
			final[j++] = input[i++];
			final[j++] = ' ';
		}
		final[j++] = input[i++];
	}
	final[j] = '\0';
	printf("before : %s\n", input);
	printf("after : %s\n", final);
	return (final);
}
