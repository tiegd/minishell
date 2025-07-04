/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:17:38 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/04 18:29:14 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_word(char *s)
{
	t_input in;

	init_index(&in);
	while (s[in.i])
	{
		skip_white_space(s, &in);
		if (s[in.i] && !is_ws(s[in.i]) && in.sq % 2 == 0 && in.dq % 2 == 0)
			in.count++;
		skip_special_char(s, &in);
		skip_white_space(s, &in);
		while (s[in.i] && !is_ws(s[in.i]) && !is_special(s[in.i]))
		{
			update_quotes(s[in.i], &in.sq, &in.dq);
			in.i++;
		}
		skip_beetwen_quotes(s, &in.i, &in.sq, &in.dq);
	}
	return (in.count);
}

static char	**ft_new_str(char **double_tab, char *s, int nb_word, t_gmalloc **head)
{
	t_input in;

	init_index(&in);
	while (s[in.i] && in.count < nb_word)
	{
		skip_white_space(s, &in);
		if (!handle_special_char(double_tab, s, &in, head))
			return (free_split(double_tab, in.count), NULL);
		skip_alpha(s, &in.sq, &in.dq, &in.i);
		if (in.sq % 2 == 0 && in.dq % 2 == 0)
		{
			if (!extract_token(double_tab, s, &in, head))
				return (free_split(double_tab, in.count), NULL);
		}
		else
		{
			skip_beetwen_quotes(s, &in.i, &in.sq, &in.dq);
			if (is_ws(s[in.i]) && in.sq % 2 == 0 && in.dq % 2 == 0)
			{
				if (!extract_token(double_tab, s, &in, head))
					return (free_split(double_tab, in.count), NULL);
			}
		}
	}
	return (double_tab);
}

/*divise la chaine de caractère selon les règles de bash, 
renvoie un tableau de string ou NULL si ca à échoué*/
char	**ft_multi_split(char *s, t_gmalloc **head)
{
	int		nb_word;
	char	**double_tab;

	if (!(s))
		return (NULL);
	if (!check_empty_s(s, ' ', '\t'))
		return (NULL);
	nb_word = ft_count_word(s);
	double_tab = gb_malloc((nb_word + 1) * sizeof(char *), head);
	// if (!(double_tab))
	// 	return (NULL);
	double_tab[nb_word] = NULL;
	double_tab = ft_new_str(double_tab, s, nb_word, head);
	free(s);
	return (double_tab);
}
