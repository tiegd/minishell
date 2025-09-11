/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:13:16 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 13:39:09 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Return 1 if it's a double quote.
Else, return 0.*/

int	is_dq(char c)
{
	if (c == 34)
		return (1);
	return (0);
}

/*Return 1 if it's a single quote.
Else, return 0.*/

int	is_sq(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

/*Return 1 if it's a quote.
Else, return 0.*/

int	is_quote(char c)
{
	if (is_dq(c) || is_sq(c))
		return (1);
	return (0);
}

/*Return 1 if it's a whitespace.
Else, return 0.*/

int	is_ws(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

/*Return 1 if it's a redirection or a pipe.
Else, return 0.*/

int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}
