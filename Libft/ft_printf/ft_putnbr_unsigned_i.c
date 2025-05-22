/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_i.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:09:26 by jpiquet           #+#    #+#             */
/*   Updated: 2024/11/27 13:22:22 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned_i(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_putnbr_unsigned_i(n / 10);
	ft_putchar_i((n % 10) + '0');
	count++;
	return (count);
}
