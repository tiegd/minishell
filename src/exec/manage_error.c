/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:46:16 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/03 19:54:42 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <sys/stat.h>
#include <errno.h>

void	put_exit_error(t_mini *mini, char *filename, char *error, int exit_status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit_tab(mini, exit_status, 0);
}

void	put_error(t_mini *mini, char *filename, char *error, int exit_status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	mini->exit_status = exit_status;
}

int    manage_error_exec(t_cmd *cmd, t_mini *mini)
{
	struct stat	buf;

	if (!cmd->args[0])
		return (0);
	if ((cmd->args[0][0] == '~' && cmd->args[0][1] == '\0') || cmd->args[0][1] == '+' || cmd->args[0][1] == '-')
	{
		put_error(mini, cmd->args[0], "Is a directory", 126);
		return (1);
	}
	if (cmd->args[0][0] == '.' && cmd->args[0][1] == '\0')
	{
		put_error(mini, cmd->args[0], "filename argument required", 2);
		return (1);
	}
	else if (stat(cmd->args[0], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			put_error(mini, cmd->args[0], "Is a directory", 126);
			return (1);
		}
	}
	return (0);
}
