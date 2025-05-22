/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:09:26 by jpiquet           #+#    #+#             */
/*   Updated: 2024/11/27 11:24:12 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex(unsigned int n, char *hex)
{
	int	count;

	count = 0;
	if (n > 15)
		count += ft_putnbr_hex(n / 16, hex);
	ft_putchar_i(hex[n % 16]);
	count++;
	return (count);
}
