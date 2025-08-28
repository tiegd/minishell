/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:13:16 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/26 09:07:54 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*retourne 1 si c'est une double quote sinon 0*/
int	is_dq(char c)
{
	if (c == 34)
		return (1);
	return (0);
}

/*retourne 1 si c'est une single quote sinon 0*/
int	is_sq(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

/*retourne 1 si c'est une quote sinon 0*/
int	is_quote(char c)
{
	if (is_dq(c) || is_sq(c))
		return (1);
	return (0);
}

/*retourne 1 si c'est un whitespace sinon 0*/
int	is_ws(char c)
{
	if (c == 32 || c == 9) /*32 = space | 9 = /t*/
		return (1);
	return (0);
}
/*return 1 if it's a redirection or a pipe, else return 0*/
int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}
