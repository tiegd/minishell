/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:17:38 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/28 14:13:51 by jpiquet          ###   ########.fr       */
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

static char	**ft_new_str(char **double_tab, char *s, int nb_word)
{
	t_input in;

	init_index(&in);
	while (s[in.i] && in.count < nb_word)
	{
		skip_white_space(s, &in);
		if (!handle_special_char(double_tab, s, &in))
			return (free_split(double_tab, in.count), NULL);
		skip_alpha(s, &in.sq, &in.dq, &in.i);
		if (in.sq % 2 == 0 && in.dq % 2 == 0)
		{
			if (!extract_token(double_tab, s, &in))
				return (free_split(double_tab, in.count), NULL);
		}
		else
		{
			skip_beetwen_quotes(s, &in.i, &in.sq, &in.dq);
			if (is_ws(s[in.i]) && in.sq % 2 == 0 && in.dq % 2 == 0)
			{
				if (!extract_token(double_tab, s, &in))
					return (free_split(double_tab, in.count), NULL);
			}
		}
	}
	return (double_tab);
}

// static char	**ft_new_str(char **double_tab, char *s, int nb_word)
// {
// 	int		i;
// 	int		index;
// 	int		count;
// 	int		sq;
// 	int		dq;

// 	count = 0;
// 	i = 0;
// 	sq = 0;
// 	dq = 0;
// 	index = 0;
// 	while (s[i] && count < nb_word)
// 	{
// 		skip_white_space(s, sq, dq, &index, &i);
// 		if (!handle_special_char(double_tab, s, &i, &index, &count))
// 			return (free_all(double_tab), NULL);
// 		skip_alpha(s, &sq, &dq, &i);
// 		if (sq % 2 == 0 && dq % 2 == 0)
// 		{
// 			if (!extract_token(double_tab, s, &i, &index, &count))
// 				return (free_split(double_tab, count), NULL);
// 		}
// 		else
// 		{
// 			skip_beetwen_quotes(s, &i, &sq, &dq);
// 			if (is_ws(s[i]) && sq % 2 == 0 && dq % 2 == 0)
// 			{
// 				if (!extract_token(double_tab, s, &i, &index, &count))
// 					return (free_split(double_tab, count), NULL);
// 			}
// 		}
// 	}
// 	return (double_tab);
// }

/*--------BON MAIS PAS NORMÉ--------*/
// static char	**ft_new_str(char **double_tab, const char *s, int nb_word)
// {
// 	int		i;
// 	int		index;
// 	int		count;
// 	int		sq_quote;
// 	int		dq_quote;

// 	count = 0;
// 	i = 0;
// 	sq_quote = 0;
// 	dq_quote = 0;
// 	index = 0;
// 	while (s[i] && count < nb_word)
// 	{
// 		if (is_ws(s[i]) && sq_quote % 2 == 0 && dq_quote % 2 == 0)
// 		{
// 			while (s[i] && is_ws(s[i]) && sq_quote % 2 == 0 && dq_quote % 2 == 0)
// 				i++;
// 			index = i;
// 		}
// 		if (s[i] && is_special(s[i]) && !is_append(s[i], s[i + 1]) && !is_here_doc(s[i], s[i + 1]))
// 		{
// 			i++;
// 			double_tab[count] = ft_substr(s, index, i - index);
// 			if (!double_tab[count])
// 				return (free_split(double_tab, count));
// 			index = i;
// 			count++;
// 		}
// 		else if (s[i] && is_append(s[i], s[i + 1]) && is_here_doc(s[i], s[i + 1]))
// 		{
// 			i += 2;
// 			double_tab[count] = ft_substr(s, index, i - index);
// 			if (!double_tab[count])
// 				return (free_split(double_tab, count));
// 			index = i;
// 			count++;
// 		}
// 		while (s[i] && !is_ws(s[i]) && !is_special(s[i]))
// 		{
// 			if (is_sq(s[i]))
// 				sq_quote++;
// 			if (is_dq(s[i]))
// 				dq_quote++;
// 			i++;
// 		}
// 		if (sq_quote % 2 == 0 && dq_quote % 2 == 0)
// 		{
// 			double_tab[count] = ft_substr(s, index, i - index);
// 			if (!double_tab[count])
// 				return (free_split(double_tab, count));
// 			index = i;
// 			count++;
// 		}
// 		else
// 		{
// 			while (s[i] && (sq_quote % 2 == 1 || dq_quote % 2 == 1))
// 			{
// 				if (is_sq(s[i]))
// 					sq_quote++;
// 				if (is_dq(s[i]))
// 					dq_quote++;
// 				i++;
// 			}
// 			if (is_ws(s[i]) && sq_quote % 2 == 0 && dq_quote % 2 == 0)
// 			{
// 				double_tab[count] = ft_substr(s, index, i - index);
// 					if (!double_tab[count])
// 						return (free_split(double_tab, count));
// 				index = i;
// 				count++;
// 			}
// 		}
// 	}
// 	return (double_tab);
// }


/*-------MAUVAIS---------*/
// static char	**ft_new_str(char **double_tab, const char *s, int nb_word)
// {
// 	int		i;
// 	int		index;
// 	int		count;
// 	int		j;
// 	int		quote;

// 	count = 0;
// 	i = 0;
// 	quote = 0;
// 	while (s[i] && count < nb_word)
// 	{
// 		j = 0;
// 		while (s[i] && is_ws(s[i]) && quote % 2 == 0)
// 			i++;
// 		index = i;
// 		while (s[i] && !is_ws(s[i]))
// 		{
// 			if (is_quote(s[i]))
// 				quote++;
// 			i++;
// 		}
// 		if (quote % 2 == 0)
// 		{
// 			double_tab[count] = malloc((i - index + 1) * sizeof(char));
// 			if (double_tab[count] == NULL)
// 				return (free_split(double_tab, count));
// 			while (index < i)
// 				double_tab[count][j++] = s[index++];
// 			double_tab[count][j] = '\0';
// 			count++;
// 		}
// 		else
// 		{
// 			while (s[i] && quote % 2 == 1)
// 			{
// 				if (s[i] && is_quote(s[i]))
// 					quote++;
// 				i++;
// 			}
// 		}	
// 	}
// 	return (double_tab);
// }

/*divise la chaine de caractère selon les règles de bash, 
renvoie un tableau de string ou NULL si ca à échoué*/
char	**ft_multi_split(char *s)
{
	int		nb_word;
	char	**double_tab;

	if (!(s))
		return (NULL);
	if (!check_empty_s(s, ' ', '\t'))
		return (NULL);
	nb_word = ft_count_word(s);
	double_tab = malloc((nb_word + 1) * sizeof(char *));
	if (!(double_tab))
		return (NULL);
	double_tab[nb_word] = NULL;
	double_tab = ft_new_str(double_tab, s, nb_word);
	return (double_tab);
}
