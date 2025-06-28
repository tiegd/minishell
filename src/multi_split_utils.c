/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:26:05 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/28 14:13:42 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_char(char **double_tab, char *s, t_input *in)
{
	if (s[in->i] && is_special(s[in->i]) && !is_append(s[in->i], s[(in->i) + 1]) && !is_here_doc(s[in->i], s[(in->i) + 1]))
	{
		(in->i)++;
		double_tab[in->count] = ft_substr(s, in->index, in->i - in->index);
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
		double_tab[in->count] = ft_substr(s, in->index, in->i - in->index);
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
	}
	else if (s[in->i] && (is_append(s[in->i], s[in->i + 1]) 
			|| is_here_doc(s[in->i], s[in->i + 1])))
	{
		(in->count)++;
		(in->i) += 2;
	}
	else
		return ;
}

int	extract_token(char **double_tab, char *s, t_input *in)
{
	double_tab[in->count] = ft_substr(s, in->index, in->i - in->index);
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
