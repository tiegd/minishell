/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:12:46 by jpiquet           #+#    #+#             */
/*   Updated: 2025/03/06 16:52:44 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	*tab;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	tab = malloc(nmemb * size);
	if (tab == 0)
		return (NULL);
	ft_bzero(tab, nmemb * size);
	return (tab);
}
