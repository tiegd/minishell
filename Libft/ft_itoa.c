/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:19:31 by marvin            #+#    #+#             */
/*   Updated: 2024/11/21 13:33:19 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_neg(int n)
{
	if (n < 0)
	{
		n = n * -1;
		return (1);
	}
	else
		return (0);
}

static int	count_nbr(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*swap_str(char	*arg)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = ft_strlen(arg) - 1;
	while (i < j)
	{
		temp = arg[i];
		arg[i] = arg[j];
		arg[j] = temp;
		i++;
		j--;
	}
	return (arg);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*arg;
	int		neg;

	i = 0;
	neg = is_neg(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		n = n * -1;
	arg = malloc(sizeof(char) * count_nbr(n) + neg + 1);
	if (!arg)
		return (NULL);
	while (n > 0)
	{
		arg[i++] = (n % 10) + 48;
		n = n / 10;
	}
	if (neg)
		arg[i++] = '-';
	arg[i] = '\0';
	return (swap_str(arg));
}
