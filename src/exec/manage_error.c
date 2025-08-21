/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:46:16 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/21 11:31:01 by gaducurt         ###   ########.fr       */
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
		// execve(cmd->args[0], cmd->args, mini->env);
		// printf("stat(paths[0], &buf) = %d\n", stat(paths[0], &buf));
		// printf("S_ISDIR(buf.st_mode) = %d\n", S_ISDIR(buf.st_mode));
		if (stat(cmd->args[0], &buf) == 0)
		{
			if (S_ISDIR(buf.st_mode))
				printf("minishell: %s: Is a directory\n", cmd->args[0]);
		}
		// if (errno == 13)
		// {
		// 	printf("minishell: %s: Is a directory\n", cmd->args[0]);
		// 	exit_tab(mini, 126);
		// }
		// if (errno == 2)
		// {
		// 	printf(RED"minishell: %s: No such file or directory\n"RESET, cmd->args[0]);
		// 	exit_tab(mini, 127);
		// }
	}
	return ;
}
