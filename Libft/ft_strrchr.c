/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:38:44 by jpiquet           #+#    #+#             */
/*   Updated: 2024/11/19 17:55:42 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	size_t			s_len;
	unsigned char	char1;

	i = 0;
	char1 = (unsigned char)c;
	s_len = ft_strlen(s);
	if (char1 == '\0')
		return ((char *)&s[s_len]);
	while (s_len > 0)
	{
		if (s[s_len] == char1)
			return ((char *)&s[s_len]);
		s_len--;
	}
	if (s[0] == char1)
		return ((char *)&s[0]);
	return (NULL);
}
