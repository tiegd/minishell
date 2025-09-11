/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:25:12 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 13:32:53 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static void	copy_dq(char *str, int *index, int *start)
{
	(*index)++;
	while (str[*index] && str[*index] != DQ)
	{
		str[*start] = str[*index];
		(*start)++;
		(*index)++;
	}
}

static void	copy_sq(char *str, int *index, int *start)
{
	(*index)++;
	while (str[*index] && str[*index] != SQ)
	{
		str[*start] = str[*index];
		(*start)++;
		(*index)++;
	}
}

/*Remove the excessive quotes in a token and return the new string.*/

char	*delete_quote(char *str)
{
	int	start;
	int	index;

	start = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == DQ)
			copy_dq(str, &index, &start);
		if (str[index] == SQ)
			copy_sq(str, &index, &start);
		if (is_quote(str[index]))
			index++;
		if (str[index] == '\0')
			break ;
		while (str[index] && !is_quote(str[index]))
			str[start++] = str[index++];
	}
	str[start] = '\0';
	return (str);
}

/*Handle the case of quotes in a token and retrun a pointer
to the head of the modified list. */

t_token	*handle_quote(t_token **token)
{
	t_token	*temp;

	temp = *token;
	while (*token)
	{
		if ((ft_strchr((*token)->content, DQ)
				|| ft_strchr((*token)->content, SQ))
			&& (*token)->type != HERE_DOC)
		{
			(*token)->content = delete_quote((*token)->content);
		}
		(*token) = (*token)->next;
	}
	return (temp);
}
