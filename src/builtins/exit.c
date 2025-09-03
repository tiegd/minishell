/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:44:45 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/03 19:40:44 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sign(char c)
{
	if (c == '-' || c == '+')
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
		print_error_exit_arg(arg);
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
	if (is_sign(nptr[i]))
	{
		if (nptr[i] == '-')
			sign = -1;
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
	int arg_count;

	printf("exit\n");
	if (args && *args)
	{
		arg_count = ft_nb_path(args);
		if (arg_count > 2)
		{
			ft_putstr_fd("minishell: exit : too many arguments\n", 2);
			mini->exit_status = 1;
			return ;
		}
		if (arg_count > 1)
		{
			if (check_exit_argument(args[1]) == 1)
			{
				print_error_exit_arg(args[1]);
				gb_free_all(head);
				exit(2);
			}
			mini->exit_status = atoi_exit(args[1], head);
		}
	}
	gb_free_all(head);
	close_fds(mini->dup_std[0], mini->dup_std[1]);
	// close(mini->dup_std[0]);
	// close(mini->dup_std[1]);
	exit(mini->exit_status);
}
