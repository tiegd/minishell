/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:46:16 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/21 12:59:53 by gaducurt         ###   ########.fr       */
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
