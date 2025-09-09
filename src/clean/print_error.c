/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:24:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 13:10:59 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_not_valid_identifier(char *str)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	print_no_such_file(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	print_error_exit_arg(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	exit_wrong_arg(char *args, t_gmalloc **head)
{
	print_error_exit_arg(args);
	gb_free_all(head);
	exit(2);
}

void	print_error_here_doc(char *eof)
{
	ft_putstr_fd("minishell: warning: delimited by end-of-file (wanted '", 2);
	ft_putstr_fd(eof, 2);
	ft_putstr_fd("')\n", 2);
}
