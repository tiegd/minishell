/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:25:12 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/17 09:45:42 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*enleve les quotes en trop dans un token et retourne la nouvelle chaine*/
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
		if (is_quote(str[index]))
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

/*gère le cas des quotes dans un token et renvoie un pointeur sur le debut de la liste qui a été modifié*/
t_token	*ft_handle_quote(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (token)
	{
		if (ft_strchr(token->content, DQ) || ft_strchr(token->content, SQ))
		{
			token->content = delete_quote(token->content);
		}
		token = token->next;
	}
	return (temp);
}
