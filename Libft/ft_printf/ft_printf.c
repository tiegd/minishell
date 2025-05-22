/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:01:46 by jpiquet           #+#    #+#             */
/*   Updated: 2024/11/27 13:20:40 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const	char *format, ...)
{
	int		i;
	int		count_c;
	va_list	args;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	i = 0;
	count_c = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
				return (-1);
			count_c += print_args(args, format[i + 1]);
			i += 2;
		}
		if (format[i] == '\0')
			break ;
		if (format[i] != '\0' && format[i] != '%')
			count_c += ft_putchar_i(format[i++]);
	}
	va_end(args);
	return (count_c);
}
