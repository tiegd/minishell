/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:05:10 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 13:35:51 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	is_operator(char c)
{
	if (c == '|' || c == '&')
		return (1);
	return (0);
}

//Check if the previous argument is a <<

int	is_eof(char	*prev)
{
	int	i;

	i = 0;
	if (skip_and_check_quotes(&i, prev))
		return (0);
	if (i > 1)
	{
		while (i > 0)
		{
			if (is_here_doc(prev[i], prev[i - 1]))
				return (1);
			i--;
		}
	}
	return (0);
}
