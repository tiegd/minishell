/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 09:56:09 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 08:29:33 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*check accessibility of pathname, return 1 if the file is exist and 
if it has permission, 0 if not*/

int	check_access_pathname(t_mini *mini, char *args)
{
	if (access(args, F_OK) != 0)
		put_error(mini, args, "Command not found", 127);
	else if (access(args, X_OK) != 0)
		put_error(mini, args, "Permission denied", 126);
	else
		return (1);
	return (0);
}

/*check accessibility of cmd, return 1 if the file is exist and if
it has permission, 0 if not*/

int	check_access_cmd(t_mini *mini, t_cmd *cmd)
{
	if (cmd->args[0][0] == '.' && cmd->args[0][1] != '/')
	{
		put_error(mini, cmd->args[0], "Command not found", 127);
		return (0);
	}
	if (access(cmd->args[0], F_OK) != 0)
		put_error(mini, cmd->args[0], "No such file or directory", 127);
	else if (access(cmd->args[0], X_OK) != 0)
		put_error(mini, cmd->args[0], "Permission denied", 126);
	else
		return (1);
	return (0);
}

// Check if the cmd exist with access().
int	ft_is_bin(t_cmd *cmd, t_mini *mini)
{
	int		i;

	i = 0;
	cmd->pathname = NULL;
	if (cmd->args[0][0] == '.')
		return (0);
	if (cmd->paths)
	{
		while (cmd->paths[i] != NULL)
		{
			if (access(cmd->paths[i], F_OK) == 0)
			{
				if (access(cmd->paths[i], X_OK) != 0)
				{
					put_error(mini, cmd->args[0], "Permission denied", 126);
					return (0);
				}
				cmd->pathname = cmd->paths[i];
				return (1);
			}
			i++;
		}
	}
	put_error(mini, cmd->args[0], "Command not found", 127);
	return (0);
}

/*Verify if the cmd can be executed, return 1 if it can or 0 if it can´t*/
int	check_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	if (!cmd->args[0])
		return (0);
	if (ft_strchr(cmd->args[0], '/') || ft_strchr(cmd->args[0], '.'))
	{
		cmd->pathname = cmd->args[0];
		if (manage_error_exec(mini->cmd, mini))
			return (0);
		if (!check_access_cmd(mini, cmd))
			return (0);
		else
			return (1);
	}
	if (extract_path(cmd, mini, head))
	{
		if (!ft_is_bin(cmd, mini))
			return (0);
		return (1);
	}
	else
		return (0);
	if (!check_access_cmd(mini, cmd))
		return (0);
	return (1);
}
