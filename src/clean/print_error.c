/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:24:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/29 07:42:09 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_not_valid_identifier(char *str)
{
	ft_putstr_fd("minishell: export: '",2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	print_no_such_file(char *str)
{
	ft_putstr_fd("minishell: ",2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory", 2);
}
