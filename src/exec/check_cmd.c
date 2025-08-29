/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 09:56:09 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/29 12:09:31 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_path_line(char **env, t_gmalloc **head)
{
	int		i;
	int		j;
	int		len;
	char	*path;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			j = 0;
			len = ft_strlen(env[i]) - 5;
			path = gb_malloc(((len + 1) * sizeof(char)), head);
			while (env[i][j + 5])
			{
				path[j] = env[i][j + 5];
				j++;
			}
			path[j] = '\0';
			return (path);
		}
		i++;
	}
	return (NULL);
}

/*check accessibility of pathname, return 1 if the file is exist and if it has permission, 0 if not*/
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

/*check accessibility of cmd, return 1 if the file is exist and if it has permission, 0 if not*/
int	check_access_cmd(t_mini *mini, t_cmd *cmd)
{
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
	put_error(mini, cmd->args[0], "Command not found", 127);
	return (0);
}

/*Extract the $PATH in env to a char**, return 1 if an array of PATH has been found or 
0 if PATH can´t be found + copy the cmd into pathname.*/
int extract_path(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	char	*line;
	int		nb_path;

	if (!(line = ft_path_line(mini->env, head)))
	{
		// put_error(mini, cmd->args[0], "No such file or directory", 127);
		cmd->pathname = cmd->args[0];
		return (0);
	}
	cmd->paths = gb_split(line, ':', head);
	nb_path = ft_nb_path(cmd->paths);
	if (cmd->args[0])
	{
		cmd->paths = ft_add_cmd(cmd->paths, nb_path, cmd, head);
		manage_error_exec(mini->cmd, mini, cmd->paths);
	}
	return (1);
}

/*Verify if the cmd can be executed, return 1 if it can or 0 if it can´t*/
int	check_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	/*On check si il y a un '/' comme ca on a juste a regarder si il existe et si il est executable.*/
	if (ft_strchr(cmd->args[0], '/'))
	{
		cmd->pathname = cmd->args[0];
		if (!check_access_cmd(mini, cmd))
			return (0);
		else
			return (1);
	}
	/*Si il n'y a pas de '/' on check si path existe
	et on test avec chaque pour voir lequel est le bon, 
	si il n'y a pas PATH on copie l'argument dans pathname.*/
	if (extract_path(cmd, mini, head))
	{
		if (!ft_is_bin(cmd, mini))
			return (0);
		// if (!check_access_pathname(mini, cmd))
		// 	return (0);
		return (1);
	}
	/*On regarde si pathname existe et est executable(renvoyer une erreur en fonction).*/
	if (!check_access_cmd(mini, cmd))
		return (0);
	return (1);
}
