/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:55:11 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/20 17:01:43 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char const s, char c)
{
	if (s == c)
		return (1);
	else
		return (0);
}

static int	count_word(char const *s, unsigned char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_sep(s[i], c))
			i++;
		if (s[i] && !is_sep(s[i], c))
			count++;
		while (s[i] && !is_sep(s[i], c))
			i++;
	}
	return (count);
}

static char	**my_strdup(char **tabf, char const *s, int word, char c)
{
	int	i;
	int	index;
	int	start;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && j < word)
	{
		index = 0;
		while (s[i] && is_sep(s[i], c))
			i++;
		start = i;
		while (s[i] && !(is_sep(s[i], c)))
			i++;
		tabf[j] = malloc(sizeof(char) * (i - start + 1));
		if (!tabf[j])
			return (free_all(tabf));
		while (start < i)
			tabf[j][index++] = s[start++];
		tabf[j][index] = '\0';
		j++;
	}
	return (tabf);
}

char	**ft_split(char const *s, char c)
{
	char	**tabf;
	int		word;

	word = count_word(s, c);
	tabf = malloc(sizeof(char *) * (word + 1));
	if (!tabf)
		return (NULL);
	tabf = my_strdup(tabf, s, word, c);
	if (!tabf)
		return (NULL);
	tabf[word] = NULL;
	return (tabf);
}
