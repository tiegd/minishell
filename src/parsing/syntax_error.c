/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 06:03:08 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/27 16:18:31 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '&')
		return (1);
	return (0);
}

/*checker si il y a quelque chose avant un opérateur*/
int	before_operator(char *prompt)
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
int	unclosed_quote(char *prompt)
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

int	skip_ws_isalnum(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && (is_ws(prompt[i]) || exp_isalnum(prompt[i])))
		i++;
	return (i);
}

int	empty_redir(char *prompt)
{
	int	i;

	i = skip_ws_isalnum(prompt);
	while (prompt[i])
	{
		if(is_special(prompt[i]) && !is_append(prompt[i], prompt[i + 1]) && !is_here_doc(prompt[i], prompt[i + 1]))
		{
			i++;
			while (prompt[i] && is_ws(prompt[i]))
				i++;
			if (prompt[i] == '\0' || prompt[i] == '\n' || is_operator(prompt[i]))
				return (1);
		}
		else if (is_append(prompt[i], prompt[i + 1]) || is_here_doc(prompt[i], prompt[i + 1]))
		{
			i += 2;
			while (prompt[i] && is_ws(prompt[i]))
				i++;
			if (prompt[i] == '\0' || prompt[i] == '\n' || is_special(prompt[i]) || is_operator(prompt[i]))
				return (1);
		}
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
	if (empty_redir(prompt))
		return (1);
	if (unclosed_quote(prompt))
		return (1);
	return (0);
}
