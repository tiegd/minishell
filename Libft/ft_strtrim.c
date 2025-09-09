/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:17:41 by marvin            #+#    #+#             */
/*   Updated: 2024/11/21 13:36:20 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*scpy;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && is_sep(s1[start], set))
		start++;
	while (end >= start && is_sep(s1[end], set))
		end--;
	scpy = malloc(sizeof(char) * (end - start + 2));
	if (scpy == 0)
		return (NULL);
	i = 0;
	while (start <= end)
		scpy[i++] = s1[start++];
	scpy[i] = '\0';
	return (scpy);
}
