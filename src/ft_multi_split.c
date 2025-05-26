/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:17:38 by gaducurt          #+#    #+#             */
/*   Updated: 2025/05/22 15:45:58 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(const char *s, char c, char d)
{
	int	nb_word;
	int	i;

	nb_word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == d))
			i++;
		if (s[i] && (s[i] != c || s[i] != d))
			nb_word++;
		while (s[i] && (s[i] != c || s[i] != d))
			i++;
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

static char	**ft_new_str(char **double_tab, const char *s, char c, char d, int nb_word)
{
	int		i;
	int		index;
	int		count;
	int		j;

	count = 0;
	i = 0;
	while (s[i] && count < nb_word)
	{
		j = 0;
		while ((s[i] == c || s[i] == d) && s[i])
			i++;
		index = i;
		while ((s[i] != c || s[i] != d) && s[i])
			i++;
		double_tab[count] = malloc((i - index + 1) * sizeof(char));
		if (double_tab[count] == NULL)
			return (free_split(double_tab, count));
		while (index < i)
			double_tab[count][j++] = s[index++];
		double_tab[count][j] = '\0';
		count++;
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

char	**ft_multi_split(char const *s, char c, char d)
{
	int		nb_word;
	char	**double_tab;

	if (!(s))
		return (NULL);
	if (!check_empty_s(s, c, d))
		return (NULL);
	nb_word = ft_count_word(s, c, d);
	double_tab = malloc((nb_word + 1) * sizeof(char *));
	if (!(double_tab))
		return (NULL);
	double_tab[nb_word] = NULL;
	double_tab = ft_new_str(double_tab, s, c, d, nb_word);
	return (double_tab);
}
