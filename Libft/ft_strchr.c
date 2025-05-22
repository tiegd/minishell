/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:33:10 by jpiquet           #+#    #+#             */
/*   Updated: 2024/11/19 17:54:33 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	size_t			s_len;
	unsigned char	char1;

	i = 0;
	s_len = ft_strlen(s);
	char1 = (unsigned char)c;
	if (char1 == '\0')
		return ((char *)&s[s_len]);
	while (s[i])
	{
		if (s[i] == char1)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == char1)
		return ((char *)&s[i]);
	return (NULL);
}
