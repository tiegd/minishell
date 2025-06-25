/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:17:38 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/25 19:08:41 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>


/*retourne 1 si c'est une double quote sinon 0*/
int	is_dq(char c)
{
	if (c == 34)
		return (1);
	return (0);
}

/*retourne 1 si c'est une single quote sinon 0*/
int	is_sq(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (is_dq(c) || is_sq(c))
		return (1);
	return (0);
}

int	is_ws(char c)
{
	if (c == 32 || c == 9) /*32 = space | 9 = /t*/
		return (1);
	return (0);
}

int	is_append(char c, char d)
{
	if (c == '>' && d == '>')
		return (1);
	return (0);
}

int	is_here_doc(char c, char d)
{
	if (c == '<' && d == '<')
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

// int	ft_count_word(const char *s)
// {
// 	int	nb_word;
// 	int	sq_quote;
// 	int	dq_quote;
// 	int	i;

// 	nb_word = 0;
// 	i = 0;
// 	sq_quote = 0;
// 	dq_quote = 0;
// 	while (s[i])
// 	{
// 		while (is_ws(s[i]) && sq_quote % 2 == 0 && dq_quote % 2 == 0)
// 			i++;
// 		if (s[i] && !is_ws(s[i]) && sq_quote % 2 == 0 && dq_quote % 2 == 0)
// 			nb_word++;
// 		if (s[i] && is_special(s[i]) && !is_append(s[i], s[i + 1]) && !is_here_doc(s[i], s[i + 1]))
// 		{
// 			nb_word++;
// 			i++;
// 		}
// 		else if (s[i] && is_append(s[i], s[i+1]) && is_here_doc(s[i], s[i+1]))
// 		{
// 			nb_word++;
// 			i += 2;
// 		}
// 		while (s[i] && !is_ws(s[i]) && !is_special(s[i]))
// 		{
// 			if (is_sq(s[i]))
// 				sq_quote++;
// 			if (is_dq(s[i]))
// 				dq_quote++;
// 			i++;
// 		}
// 		while (s[i] && (sq_quote % 2 == 1 || dq_quote % 2 == 1))
// 		{
// 			if (is_sq(s[i]))
// 				sq_quote++;
// 			if (is_dq(s[i]))
// 				dq_quote++;
// 			i++;
// 		}
// 	}
// 	return (nb_word);
// }

static char	**free_split(char **double_tab, int nb_word)
{
	int	i;

	i = 0;
	while (i < nb_word)
	{
		free(double_tab[i]);
		i++;
	}
	free(double_tab);
	return (NULL);
}

static void		skip_white_space(char *s, int sq, int dq, int *index, int *i)
{
	if (is_ws(s[*i]) && sq % 2 == 0 && dq % 2 == 0)
	{
		while (s[*i] && is_ws(s[*i]) && sq % 2 == 0 && dq % 2 == 0)
			(*i)++;
		*index = *i;
	}
}

static void	update_quotes(char c, int *sq, int *dq)
{
	if (is_sq(c))
		(*sq)++;
	else if (is_dq(c))
		(*dq)++;
}

static int		handle_special_char(char **double_tab, char *s, int *i, int *index, int *count)
{
	if (s[*i] && is_special(s[*i]) && !is_append(s[*i], s[(*i) + 1]) && !is_here_doc(s[*i], s[(*i) + 1]))
	{
		(*i)++;
		double_tab[*count] = ft_substr(s, *index, *i - *index);
		if (!double_tab[*count])
			return (0);
		*index = *i;
		(*count)++;
		return (1);
	}
	else if (s[*i] && is_append(s[*i], s[(*i) + 1]) && is_here_doc(s[*i], s[(*i) + 1]))
	{
		(*i) += 2;
		double_tab[*count] = ft_substr(s, *index, *i - *index);
		if (!double_tab[*count])
			return (0);
		*index = *i;
		(*count)++;
		return (1);
	}
	return (2);
}

static int	extract_token(char **double_tab, char *s, int *i, int *index, int *count)
{
	double_tab[*count] = ft_substr(s, *index, *i - *index);
	if (!double_tab[*count])
		return (0);
	*index = *i;
	(*count)++;
	return (1);
}

static void	skip_alpha(char *s, int *sq, int *dq, int *i)
{
	while (s[*i] && !is_ws(s[*i]) && !is_special(s[*i]))
	{
		update_quotes(s[*i], sq, dq);
		(*i)++;
	}
}

static void	skip_beetwen_quotes(char *s, int *i, int *sq, int *dq)
{
	while (s[*i] && (*sq % 2 == 1 || *dq % 2 == 1))
	{
		update_quotes(s[*i], sq, dq);
		(*i)++;
	}
}

static char	**ft_new_str(char **double_tab, char *s, int nb_word)
{
	t_input in = {0};

	while (s[in.i] && in.count < nb_word)
	{
		skip_white_space(s, in.sq, in.dq, &in.index, &in.i);
		if (!handle_special_char(double_tab, s, &in.i, &in.index, &in.count))
			return (free_all(double_tab), NULL);
		skip_alpha(s, &in.sq, &in.dq, &in.i);
		if (in.sq % 2 == 0 && in.dq % 2 == 0)
		{
			if (!extract_token(double_tab, s, &in.i, &in.index, &in.count))
				return (free_split(double_tab, in.count), NULL);
		}
		else
		{
			skip_beetwen_quotes(s, &in.i, &in.sq, &in.dq);
			if (is_ws(s[in.i]) && in.sq % 2 == 0 && dq % 2 == 0)
			{
				if (!extract_token(double_tab, s, &in.i, &in.index, &in.count))
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

static int	check_empty_s(const char *s, char c, char d)
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

/*divise la chaine de caractère selon les règles de bash, 
renvoie un tableau de string ou NULL si ca à échoué*/

char	**ft_multi_split(char const *s)
{
	int		nb_word;
	char	**double_tab;

	if (!(s))
		return (NULL);
	if (!check_empty_s(s, ' ', '\t'))
		return (NULL);
	nb_word = ft_count_word(s);
	// printf("count word = %d\n", nb_word);
	double_tab = malloc((nb_word + 1) * sizeof(char *));
	if (!(double_tab))
		return (NULL);
	double_tab[nb_word] = NULL;
	double_tab = ft_new_str(double_tab, s, nb_word);
	return (double_tab);
}
