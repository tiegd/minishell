/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:44:45 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/21 16:43:07 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **args, int exit_status, t_gmalloc **head)
{
	int arg_count;

	arg_count = ft_nb_path(args);
	if (arg_count > 1)
	{
		ft_putstr_fd("exit : too many arguments", 2);
		return ;
	}
	printf("exit\n");
	gb_free_all(head);
	exit(exit_status);
}
