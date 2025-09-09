/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 06:03:08 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 08:39:15 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*checker si il y a quelque chose avant un opérateur*/
static int	before_operator(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && is_ws(prompt[i]))
		i++;
	if (prompt[i] && is_operator(prompt[i]))
		return (1);
	return (0);
}

/*Checker si il y a une quote qui n'a pas été fermé */
static int	unclosed_quote(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == SQ)
		{
			i++;
			while (prompt[i] && prompt[i] != SQ)
				i++;
			if (prompt[i] == '\0')
				return (1);
		}
		if (prompt[i] == DQ)
		{
			i++;
			while (prompt[i] && prompt[i] != DQ)
				i++;
			if (prompt[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	empty_redir(char *prompt)
{
	int	i;

	i = skip_ws_isalnum(prompt);
	while (prompt[i])
	{
		if (prompt[i] == SQ)
			skip_quotes(prompt, &i, SQ);
		if (prompt[i] == DQ)
			skip_quotes(prompt, &i, DQ);
		if (is_operator(prompt[i]))
		{
			if (operator_syntax_error(prompt, &i) == 1)
				return (1);
		}
		if (is_redir(prompt[i]))
		{
			if (redir_syntax_error(prompt, &i) == 1)
				return (1);
		}
		if (prompt[i])
			i++;
	}
	return (0);
}

int	syntax_error(char *prompt)
{
	if (char_not_required(prompt))
		return (1);
	if (before_operator(prompt))
		return (1);
	if (unclosed_quote(prompt))
		return (1);
	if (empty_redir(prompt))
		return (1);
	return (0);
}

static int	char_not_required(char *prompt)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (prompt[i])
	{
		if (prompt[i] == SQ)
			sq++;
		if (prompt[i] == DQ)
			dq++;
		if (not_required(prompt[i]) && sq % 2 == 0 && dq % 2 == 0)
			return (1);
		i++;
	}
	return (0);
}

