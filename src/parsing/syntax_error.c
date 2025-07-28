/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 06:03:08 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/23 10:09:38 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Liste des caractères qu'on ne doit pas traiter :  ( ) \ & * ............*/ 

int	not_required(char c)
{
	if (c == '(')
		return (1);
	if (c == ')')
		return (1);
	if (c == BS)
		return (1);
	if (c == '&')
		return (1);
	if (c == '*')
		return (1);
	return (0);
}

/*checker si il y a un caractere hors sujet et si il n'est pas compris entre quote*/
int char_not_required(char *prompt)
{
	int i;
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
			while (prompt[i] && is_ws(prompt[i]))
				i++;
			// if (prompt[i] == '\0' || prompt[i] == '\n' || is_special(prompt[i]) || is_operator(prompt[i]))
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
	// if (after_operator(prompt))
	// 	return (1);
	if (empty_redir(prompt))
		return (1);
	if (unclosed_quote(prompt))
		return (1);
	return (0);
}
