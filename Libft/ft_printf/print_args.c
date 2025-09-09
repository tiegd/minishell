/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:00:07 by jpiquet           #+#    #+#             */
/*   Updated: 2024/11/27 11:15:12 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_args(va_list args, const char c)
{
	int	res;

	res = 0;
	if (c == '%')
		res = ft_putchar_i('%');
	else if (c == 'c')
		res = ft_putchar_i((char)va_arg(args, int));
	else if (c == 'i' || c == 'd')
		res = ft_putnbr_i(va_arg(args, int));
	else if (c == 's')
		res = ft_putstr_i(va_arg(args, char *));
	else if (c == 'u')
		res = ft_putnbr_unsigned_i(va_arg(args, unsigned int));
	else if (c == 'p')
		res = ft_put_address(va_arg(args, size_t));
	else if (c == 'x')
		res = ft_putnbr_hex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		res = ft_putnbr_hex(va_arg(args, unsigned int), "0123456789ABCDEF");
	return (res);
}
