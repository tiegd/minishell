/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:17:38 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/12 16:54:35 by jpiquet          ###   ########.fr       */
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

int	ft_count_word(const char *s)
{
	int	nb_word;
	int	quote;
	int	i;

	nb_word = 0;
	i = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] && is_ws(s[i]) && quote % 2 == 0)
		{
			i++;
		}
		if (s[i] && !is_ws(s[i]) && quote % 2 == 0)
		{
			nb_word++;
		}
		while (s[i] && !is_ws(s[i]))
		{
			if (is_quote(s[i]))
			{
				quote++;
			}
			i++;
		}
		while (s[i] && quote % 2 == 1)
		{
			if (s[i] && is_quote(s[i]))
				quote++;
			i++;
		}
	}
	return (nb_word);
}

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

static char	**ft_new_str(char **double_tab, const char *s, int nb_word)
{
	int		i;
	int		index;
	int		count;
	int		j;
	int		quote;

	count = 0;
	i = 0;
	quote = 0;
	while (s[i] && count < nb_word)
	{
		j = 0;
		while (s[i] && is_ws(s[i]) && quote % 2 == 0)
			i++;
		index = i;
		while (s[i] && !is_ws(s[i]))
		{
			if (is_quote(s[i]))
				quote++;
			i++;
		}
		if (quote % 2 == 0)
		{
			double_tab[count] = malloc((i - index + 1) * sizeof(char));
			if (double_tab[count] == NULL)
				return (free_split(double_tab, count));
			while (index < i)
				double_tab[count][j++] = s[index++];
			double_tab[count][j] = '\0';
			count++;
		}
		else
		{
			while (s[i] && quote % 2 == 1)
			{
				if (s[i] && is_quote(s[i]))
					quote++;
				i++;
			}
		}	
	}
	return (double_tab);
}

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

//Pareil que split mais split sur a partir de char set.
char	**ft_multi_split(char const *s)
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
