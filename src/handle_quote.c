/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:25:12 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/13 14:19:42 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_quote(char *str)
{
	int	start;
	int index;
	// int	dq;
	// int	sq;

	start = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == DQ)
		{
			index++;
			while(str[index] && str[index] != DQ)
			{
				str[start] = str[index];
				start++;
				index++;
			}
		}
		if (str[index] == SQ)
		{
			index++;
			while(str[index] && str[index] != SQ)
			{
				str[start] = str[index];
				start++;
				index++;
			}
		}
		if (is_quote(str[index])) //&& str[index + 1])
			index++;
		if (str[index] == '\0')
			break;
		str[start] = str[index];
		start++;
		index++;
	}
	str[start] = '\0';
	return (str);
}

t_token	*ft_handle_quote(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (token)
	{
		if (ft_strchr(token->content, DQ) || ft_strchr(token->content, SQ))
		{
			printf("HELLO\n");
			token->content = delete_quote(token->content);
		}
		token = token->next;
	}
	return (temp);
}
