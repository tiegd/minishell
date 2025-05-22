/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:10:03 by jpiquet           #+#    #+#             */
/*   Updated: 2024/11/19 17:53:30 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_temp;
	size_t				i;

	i = 0;
	s_temp = (const unsigned char *)s;
	while (i < n)
	{
		if (s_temp[i] == (unsigned char)c)
			return ((void *)&s_temp[i]);
		i++;
	}
	return (NULL);
}
