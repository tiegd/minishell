/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_count_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:44:33 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/12 16:17:41 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

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
	// printf("quote = %d\n", quote);
	return (nb_word);
}

// int main()
// {
// 	int count;

// 	count = ft_count_word(""echo "bonjour"'ca''va'"comment    oui"")
// }

int	main()
{
	char	*line;
	int		count;

	while ((line = readline("minizeub > ")) != NULL)
	{
		if(*line)
		{
			add_history(line);
		}
		count = ft_count_word(line);
		printf("word = %d\n", count);
		free(line);
	}
	return (0);
}
