/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_split_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:26:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/02 15:21:27 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		skip_white_space(char *s, t_input *in)
{
	if (is_ws(s[in->i]) && in->sq % 2 == 0 && in->dq % 2 == 0)
	{
		while (s[in->i] && is_ws(s[in->i]) && in->sq % 2 == 0 && in->dq % 2 == 0)
			(in->i)++;
		in->index = in->i;
	}
}

void	update_quotes(char c, int *sq, int *dq)
{
	if (is_sq(c))
		(*sq)++;
	else if (is_dq(c))
		(*dq)++;
}

void	skip_alpha(char *s, int *sq, int *dq, int *i)
{
	while (s[*i] && !is_ws(s[*i]) && !is_special(s[*i]))
	{
		update_quotes(s[*i], sq, dq);
		(*i)++;
	}
}

void	skip_beetwen_quotes(char *s, int *i, int *sq, int *dq)
{
	while (s[*i] && (*sq % 2 == 1 || *dq % 2 == 1))
	{
		update_quotes(s[*i], sq, dq);
		(*i)++;
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
