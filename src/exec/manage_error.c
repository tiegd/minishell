/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:46:16 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/27 15:15:57 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <sys/stat.h>
#include <errno.h>

void    manage_error_exec(t_cmd *cmd, t_mini *mini, char **paths)
{
	struct stat	buf;
	
    if ((cmd->args[0][0] == '~' && cmd->args[0][1] == '\0') || cmd->args[0][1] == '+' || cmd->args[0][1] == '-')
	{
		printf("minishell: %s: Is a directory\n", paths[0]);
		exit_tab(mini, 126);
	}
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		if (cmd->args[0][0] == '.' && cmd->args[0][1] == '\0')
		{
			printf("minishell: %s: filename argument required\n", cmd->args[0]);
			exit_tab(mini, 2);
		}
		if (stat(cmd->args[0], &buf) == 0)
		{
			if (S_ISDIR(buf.st_mode))
				printf("minishell: %s: Is a directory\n", cmd->args[0]);
		}
	}
	return ;
}

void	print_error(t_mini *mini, char *filename, char *error, int exit_status)
{
	printf(RED"minishell: %s: %s\n"RESET, filename, error);
	exit_tab(mini, exit_status);
}
