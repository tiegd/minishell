/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 06:03:08 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/16 13:59:44 by jpiquet          ###   ########.fr       */
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

int	unclosed_quote(char *prompt)
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
		i++;
	}
	if (dq % 2 != 0 || sq % 2 != 0)
		return (1);
	return (0);
}

int	empty_redir(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && (is_ws(prompt[i]) || exp_isalnum(prompt[i])))
		i++;
	while (prompt[i])
	{
		if(is_special(prompt[i]) && !is_append(prompt[i], prompt[i + 1]) && !is_here_doc(prompt[i], prompt[i + 1]))
		{
			i++;
			while (prompt[i] && (is_ws(prompt[i]) || exp_isalnum(prompt[i])))
				i++;
			if (prompt[i] == '\n' || is_special(prompt[i]) || is_operator(prompt[i]))
				return (1);
		}
		else if (is_append(prompt[i], prompt[i + 1]) || is_here_doc(prompt[i], prompt[i + 1]))
		{
			i += 2;
			while (prompt[i] && (is_ws(prompt[i]) || exp_isalnum(prompt[i])))
				i++;
			if (prompt[i] == '\n' || is_special(prompt[i]) || is_operator(prompt[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	syntax_error(char *prompt)
{
	if (before_operator(prompt))
		return (1);
	else if (empty_redir(prompt))
		return (1);
	else if (unclosed_quote(prompt))
		return (1);
	return (0);
}
