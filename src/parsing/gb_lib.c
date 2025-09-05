/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerzone <amerzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:47:50 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/05 12:25:26 by amerzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gb_substr(char const *s, unsigned int start, size_t len, t_gmalloc **head)
{
	size_t			i;
	char			*strtemp;
	size_t			f_len;

	f_len = ft_strlen(s);
	if (start >= f_len)
		return (gb_strdup("", head));
	if (len + start > f_len)
		len = f_len - start;
	i = 0;
	strtemp = gb_malloc(sizeof(char) * (len + 1), head);
	while (i < len)
	{
		strtemp[i] = s[start];
		i++;
		start++;
	}
	strtemp[i] = '\0';
	return (strtemp);
}

char	*gb_strdup(char *s, t_gmalloc **gmalloc)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(s);
	dest = gb_malloc(sizeof(char) * (len + 1), gmalloc);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	// gfree(s, gmalloc);
	return (dest);
}

char	*gb_strjoin_custom(char *s1, char *s2, t_gmalloc **head)
{
	int		tlen;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	tlen = ft_strlen(s1) + ft_strlen(s2);
	str = gb_malloc(sizeof(char) * tlen + 1, head);
	if (str == 0)
		return (NULL);
	while (s1[j] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	gfree(s1, head);
	return (str);
}

char	*gb_strjoin(char *s1, char *s2, t_gmalloc **head)
{
	int		tlen;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	tlen = ft_strlen(s1) + ft_strlen(s2);
	str = gb_malloc(sizeof(char) * tlen + 1, head);
	if (str == 0)
		return (NULL);
	while (s1[j] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
