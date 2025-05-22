/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:41:42 by jpiquet           #+#    #+#             */
/*   Updated: 2024/11/19 17:55:59 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*strtemp;
	size_t			f_len;

	f_len = ft_strlen(s);
	if (start >= f_len)
		return (ft_strdup(""));
	if (len + start > f_len)
		len = f_len - start;
	i = 0;
	strtemp = malloc(sizeof(char) * (len + 1));
	if (strtemp == 0)
		return (NULL);
	while (i < len)
	{
		strtemp[i] = s[start];
		i++;
		start++;
	}
	strtemp[i] = '\0';
	return (strtemp);
}
