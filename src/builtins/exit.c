/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:44:45 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/16 11:46:11 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **args, int exit_status, t_gmalloc **head)
{
	int arg_count;

	arg_count = ft_nb_path(args);
	// if (args > 1)
	if (arg_count > 1)
	{
		ft_putstr_fd("exit : too much arguments", 2);
		return ;
	}
	printf("exit\n");
	gb_free_all(head);
	exit(exit_status);
}
