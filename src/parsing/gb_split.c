/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:02:30 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/08 12:04:34 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	**my_strdup(char **tabf, char const *s, char c, t_gmalloc **head)
{
	int	i;
	int	index;
	int	start;
	int	j;
	int	word;

	i = 0;
	j = 0;
	word = count_word(s, c);
	while (s[i] && j < word)
	{
		index = 0;
		while (s[i] && is_sep(s[i], c))
			i++;
		start = i;
		while (s[i] && !(is_sep(s[i], c)))
			i++;
		tabf[j] = gb_malloc((sizeof(char) * (i - start + 1)), head);
		while (start < i)
			tabf[j][index++] = s[start++];
		tabf[j][index] = '\0';
		j++;
	}
	return (tabf);
}

char	**gb_split(char *s, char c, t_gmalloc **head)
{
	char	**tabf;
	int		word;

	word = count_word(s, c);
	tabf = gb_malloc((sizeof(char *) * (word + 1)), head);
	tabf = my_strdup(tabf, s, c, head);
	tabf[word] = NULL;
	return (tabf);
}
