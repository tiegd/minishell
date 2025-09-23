/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_split_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:26:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 14:24:29 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "gblib.h"

void	skip_white_space(char *s, t_input *in)
{
	if (is_ws(s[in->i]) && in->sq % 2 == 0 && in->dq % 2 == 0)
	{
		while (s[in->i] && is_ws(s[in->i])
			&& in->sq % 2 == 0 && in->dq % 2 == 0)
			(in->i)++;
		in->index = in->i;
	}
}

void	init_index(t_input *in)
{
	in->count = 0;
	in->i = 0;
	in->index = 0;
	in->sq = 0;
	in->dq = 0;
}
