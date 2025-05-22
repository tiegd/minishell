/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:04:12 by jpiquet           #+#    #+#             */
/*   Updated: 2024/11/27 13:57:46 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_i(char *s)
{
	size_t	len;

	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = ft_strlen(s);
	write (1, s, len);
	return (len);
}
