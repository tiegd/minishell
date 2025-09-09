/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:17:38 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/09 17:09:43 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "gblib.h"
#include "exec.h"

static void	skip_quote(char *str, char quote, t_input *in)
{
	if (quote == SQ)
	{
		(in->i)++;
		while (str[in->i] && str[in->i] != SQ)
			(in->i)++;
	}
	else if (quote == DQ)
	{
		(in->i)++;
		while (str[in->i] && str[in->i] != DQ)
			(in->i)++;
	}
}

static int	count_word(char *s)
{
	t_input	in;

	init_index(&in);
	while (s[in.i])
	{
		skip_white_space(s, &in);
		if (s[in.i] && !is_special(s[in.i]) && !is_ws(s[in.i]))
			in.count++;
		skip_special_char(s, &in);
		while (s[in.i] && !is_special(s[in.i]) && !is_ws(s[in.i]))
		{
			if (is_quote(s[in.i]))
				skip_quote(s, s[in.i], &in);
			in.i++;
		}
	}
	return (in.count);
}

static char	**new_str(char **tab, char *s, int nb_word, t_gmalloc **head)
{
	t_input	in;

	init_index(&in);
	while (s[in.i] && in.count < nb_word)
	{
		skip_white_space(s, &in);
		while (s[in.i] && is_special(s[in.i]))
			handle_special_char(tab, s, &in, head);
		while (s[in.i] && !is_special(s[in.i]) && !is_ws(s[in.i]))
		{
			if (is_quote(s[in.i]))
				skip_quote(s, s[in.i], &in);
			in.i++;
		}
		if (!extract_token(tab, s, &in, head))
			return (free_split(tab, in.count, head), NULL);
	}
	return (tab);
}

/*split the string under the bash rules, return an array of string*/
char	**multi_split(char *s, t_gmalloc **head)
{
	int		nb_word;
	char	**double_tab;

	if (!(s))
		return (NULL);
	if (!check_empty_s(s, ' ', '\t'))
		return (NULL);
	nb_word = count_word(s);
	double_tab = gb_malloc((nb_word + 1) * sizeof(char *), head);
	double_tab[nb_word] = NULL;
	double_tab = new_str(double_tab, s, nb_word, head);
	gfree(s, head);
	return (double_tab);
}
