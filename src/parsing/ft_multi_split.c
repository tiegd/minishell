/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:17:38 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/03 18:50:31 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quote(char *str, char quote, t_input *in)
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

int	ft_count_word(char *s)
{
	t_input in;

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

//  int count_word(char **double_tab, char *s, int nb_word, t_gmalloc **head)
// {
// 	t_input in;

// 	init_index(&in);
// 	while (s[in.i])
// 	{
// 		skip_white_space(s, &in);
// 		if (s[in.i] && is_special(s[in.i]))
// 			skip_special_char(s, &in);
// 		skip_alpha(s, &in.sq, &in.dq, &in.i);
// 		if (in.sq % 2 == 1 || in.dq % 2 == 1)
// 		{
// 			skip_beetwen_quotes(s, &in.i, &in.sq, &in.dq);
// 			if (s[in.i] && !is_special(s[in.i]))
// 				continue ;
// 		}
// 		if (in.sq % 2 == 0 || in.dq % 2 == 0)
// 		{
// 			if (!extract_token(double_tab, s, &in, head))
// 				return (free_split(double_tab, in.count, head), NULL);
// 		}
// 	}
// 	return (double_tab);
// }

// int	ft_count_word(char *s)
// {
// 	t_input in;

// 	init_index(&in);
// 	while (s[in.i])
// 	{
// 		skip_white_space(s, &in);
// 		if (s[in.i] && !is_special(s[in.i]) && !is_ws(s[in.i]) && in.sq % 2 == 0 && in.dq % 2 == 0)
// 			in.count++;
// 		skip_special_char(s, &in);
// 		// skip_white_space(s, &in);
// 		skip_beetwen_quotes(s, &in.i, &in.sq, &in.dq);
// 		while (s[in.i] && !is_ws(s[in.i]) && !is_special(s[in.i]))
// 		{
// 			update_quotes(s[in.i], &in.sq, &in.dq);
// 			in.i++;
// 		}
// 		skip_beetwen_quotes(s, &in.i, &in.sq, &in.dq);
// 		// if (s[in.i] && !is_special(s[in.i]) && !is_ws(s[in.i]))
		
// 	}
// 	return (in.count);
// }

static char	**ft_new_str(char **double_tab, char *s, int nb_word, t_gmalloc **head)
{
	t_input in;

	init_index(&in);
	while (s[in.i] && in.count < nb_word)
	{
		skip_white_space(s, &in);
		while (s[in.i] && is_special(s[in.i]))
			handle_special_char(double_tab, s, &in, head);
		skip_alpha(s, &in.sq, &in.dq, &in.i);
		if (in.sq % 2 == 1 || in.dq % 2 == 1)
		{
			skip_beetwen_quotes(s, &in.i, &in.sq, &in.dq);
			if (s[in.i] && !is_special(s[in.i]))
				continue ;
		}
		if (in.sq % 2 == 0 || in.dq % 2 == 0)
		{
			if (!extract_token(double_tab, s, &in, head))
				return (free_split(double_tab, in.count, head), NULL);
		}
	}
	return (double_tab);
}

// static char	**ft_new_str(char **double_tab, char *s, int nb_word, t_gmalloc **head)
// {
// 	t_input in;

// 	init_index(&in);
// 	while (s[in.i] && in.count < nb_word)
// 	{
// 		skip_white_space(s, &in);
// 		while (s[in.i] && is_special(s[in.i]))
// 			handle_special_char(double_tab, s, &in, head);
// 		skip_alpha(s, &in.sq, &in.dq, &in.i);
// 		if (in.sq % 2 == 1 || in.dq % 2 == 1)
// 		{
// 			skip_beetwen_quotes(s, &in.i, &in.sq, &in.dq);
// 			if (s[in.i] && !is_special(s[in.i]))
// 				continue ;
// 		}
// 		if (in.sq % 2 == 0 || in.dq % 2 == 0)
// 		{
// 			if (!extract_token(double_tab, s, &in, head))
// 				return (free_split(double_tab, in.count, head), NULL);
// 		}
// 	}
// 	return (double_tab);
// }

/*split the string under the bash rules, return an array of string*/
char	**ft_multi_split(char *s, t_gmalloc **head)
{
	int		nb_word;
	char	**double_tab;

	if (!(s))
		return (NULL);
	if (!check_empty_s(s, ' ', '\t'))
		return (NULL);
	nb_word = ft_count_word(s);
	printf("nb world = %d\n", nb_word);
	double_tab = gb_malloc((nb_word + 1) * sizeof(char *), head);
	double_tab[nb_word] = NULL;
	double_tab = ft_new_str(double_tab, s, nb_word, head);
	gfree(s, head);
	return (double_tab);
}
