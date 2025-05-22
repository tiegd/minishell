/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_address.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:17:22 by jpiquet           #+#    #+#             */
/*   Updated: 2024/11/26 13:31:18 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_address(size_t n, char *hex)
{
	int	count;

	count = 0;
	if (n > 15)
		count += ft_putnbr_address(n / 16, hex);
	ft_putchar_i(hex[n % 16]);
	count++;
	return (count);
}

int	ft_put_address(size_t address)
{
	int	count;

	if (address == 0)
		return (ft_putstr_i("(nil)"));
	write(1, "0x", 2);
	count = 2;
	count += ft_putnbr_address(address, "0123456789abcdef");
	return (count);
}
