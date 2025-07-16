/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:26:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/16 10:37:57 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_char(char **double_tab, char *s, t_input *in, t_gmalloc **head)
{
	if (s[in->i] && is_special(s[in->i]) && !is_append(s[in->i], s[(in->i) + 1]) && !is_here_doc(s[in->i], s[(in->i) + 1]))
	{
		(in->i)++;
		double_tab[in->count] = gb_substr(s, in->index, in->i - in->index, head);
		if (!double_tab[in->count])
			return (0);
		in->index = in->i;
		(in->count)++;
		skip_white_space(s, in);
		return (1);
	}
	else if (s[in->i] && (is_append(s[in->i], s[(in->i) + 1]) || is_here_doc(s[in->i], s[(in->i) + 1])))
	{
		(in->i) += 2;
		double_tab[in->count] = gb_substr(s, in->index, in->i - in->index, head);
		if (!double_tab[in->count])
			return (0);
		in->index = in->i;
		(in->count)++;
		skip_white_space(s, in);
		return (1);
	}
	return (2);
}

void	skip_special_char(char *s, t_input *in)
{
	if (s[in->i] && is_special(s[in->i]) && !is_append(s[in->i], s[in->i + 1]) 
		&& !is_here_doc(s[in->i], s[in->i + 1]))
	{
		(in->count)++;
		(in->i)++;
		if (s[in->i] && !is_special(s[in->i]) && !is_ws(s[in->i]) && in->sq % 2 == 0 && in->dq % 2 == 0)
			in->count++;
	}
	else if (s[in->i] && (is_append(s[in->i], s[in->i + 1]) 
			|| is_here_doc(s[in->i], s[in->i + 1])))
	{
		(in->count)++;
		(in->i) += 2;
		if (s[in->i] && !is_special(s[in->i]) && !is_ws(s[in->i]) && in->sq % 2 == 0 && in->dq % 2 == 0)
			in->count++;
	}
	else
		return ;
}

int	extract_token(char **double_tab, char *s, t_input *in, t_gmalloc **head)
{
	double_tab[in->count] = gb_substr(s, in->index, in->i - in->index, head);
	if (!double_tab[in->count])
		return (0);
	in->index = in->i;
	(in->count)++;
	return (1);
}

int	check_empty_s(const char *s, char c, char d)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == d)
			i++;
		else
			return (1);
	}
	return (0);
}

int	count_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
