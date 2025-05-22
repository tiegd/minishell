/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:39:34 by jpiquet           #+#    #+#             */
/*   Updated: 2025/01/24 14:53:28 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_putchar_i(char c);
int		print_args(va_list args, const char c);
int		ft_putstr_i(char *s);
int		ft_putnbr_i(int n);
int		ft_putnbr_unsigned_i(unsigned int n);
int		ft_putnbr_hex(unsigned int n, char *hex);
int		ft_put_address(size_t address);

#endif
