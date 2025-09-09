/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:20:04 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/08 14:41:05 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dollar_existence(char *prompt, int *i, char quote)
{
	int	res;

	res = 0;
	(*i)++;
	while (prompt[*i] && prompt[*i] != quote)
	{
		if (prompt[*i] == '$')
			res = 1;
		(*i)++;
	}
	return (res);
}

int	which_quote(char *prompt, int *index)
{
	while (prompt[*index])
	{
		if (prompt[*index] == '$')
		{
			(*index)++;
			return (DQ);
		}
		if (prompt[*index] == DQ && check_dollar_existence(prompt, index, DQ))
		{
			while (prompt[*index] != DQ)
				(*index)++;
			(*index)++;
			return (DQ);
		}
		if (prompt[*index] == SQ && check_dollar_existence(prompt, index, SQ))
		{
			while (prompt[*index] != SQ)
				(*index)++;
			(*index)++;
			return (SQ);
		}
		(*index)++;
	}
	return (DQ);
}

int	skip_and_check_quotes(int *i, char *prev)
{
	while (prev[*i])
	{
		if (prev[*i] == SQ)
		{
			(*i)++;
			while (prev[*i] && prev[*i] != SQ)
				(*i)++;
			if (prev[*i] == '\0')
				return (true);
		}
		if (prev[*i] == DQ)
		{
			(*i)++;
			while (prev[*i] && prev[*i] != DQ)
				(*i)++;
			if (prev[*i] == '\0')
				return (true);
		}
		(*i)++;
	}
	return (false);
}
