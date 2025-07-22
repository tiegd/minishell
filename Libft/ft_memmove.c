/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerzone <amerzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:04:31 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/22 14:27:31 by amerzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	// size_t		i;
	char		*d;
	const char	*s;

	// i = 0;
	d = (char *)dest;
	s = (const char *)src;
	if (dest == 0 && src == 0)
		return (NULL);
	if (d < s)
	{
		return (ft_memcpy(d, s, n));
	}
	else
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return (d);
}
