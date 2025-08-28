/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 09:14:15 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/26 11:27:08 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Liste des caractères qu'on ne doit pas traiter :  ( ) \ & * ............*/ 
static int	not_required(char c)
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
