/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 06:03:08 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/16 07:44:14 by jpiquet          ###   ########.fr       */
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

int	empty_redir(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && is_ws(prompt[i]))
		i++;
	
}

int	syntax_error(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && is_ws(prompt[i]))
		i++;
	if (prompt[i] && is_operator(prompt[i]))
		return (1);
	return (0);
}