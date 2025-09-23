/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:44:45 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 11:39:13 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "clean.h"
#include "gblib.h"
#include "builtins.h"
#include "fd.h"
#include <stdio.h>
#include <readline/readline.h>

int	is_sign(char c)
{
	if (c == '-')
		return (-1);
	else if (c == '+')
		return (1);
	else
		return (0);
}

int	check_exit_argument(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '\0')
		return (1);
	while (arg[i] && is_ws(arg[i]))
		i++;
	if (arg[i] && is_sign(arg[i]))
		i++;
	if (arg[i] && !ft_isdigit(arg[i]))
		return (1);
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	while (arg[i])
	{
		if (!is_ws(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

void	check_limits(long long n, char *arg, t_gmalloc **head)
{
	if (n > INT_MAX || n < INT_MIN)
	{
		print_error_exit_arg(arg, head);
		gb_free_all(head);
		exit(2);
	}
}

int	atoi_exit(char *nptr, t_gmalloc **head)
{
	int					i;
	long long			n;
	int					sign;

	i = 0;
	n = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign = is_sign(nptr[i]);
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		n = n * 10 + (nptr[i] - 48);
		check_limits(n, nptr, head);
		i++;
	}
	if (n > 256)
		n = n % 256;
	if (sign == -1)
		n = 256 - n;
	return ((unsigned char)n);
}

void	ft_exit(char **args, t_mini *mini, t_gmalloc **head)
{
	int	arg_count;

	if (mini->nb_pipe == 0)
		ft_putstr_fd("exit\n", 1);
	if (args && *args)
	{
		arg_count = ft_nb_path(args);
		if (arg_count > 1)
		{
			if (check_exit_argument(args[1]) == 1)
				exit_wrong_arg(args[1], mini);
			mini->exit_status = atoi_exit(args[1], head);
		}
		if (arg_count > 2)
		{
			ft_putstr_fd("minishell: exit : too many arguments\n", 2);
			mini->exit_status = 1;
			return ;
		}
	}
	gb_free_all(head);
	close_fds(mini->dup_std[0], mini->dup_std[1]);
	rl_clear_history();
	exit(mini->exit_status);
}
