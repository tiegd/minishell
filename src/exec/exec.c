/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:50:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/04 10:56:37 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if the cmd exist with access().

char	*ft_is_bin(char **paths, int nb_path)
{
	int		i;

	i = 0;
	while (i <= nb_path)
	{
		if (access(paths[i], F_OK) == 0)
			return (paths[i]);
		i++;
	}
	return (NULL);
}

// Run the cmd if it's a builtin.

int	ft_exec_builtin(t_cmd *cmd, char **env)
{
	if (ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	if (ft_strcmp(cmd->args[0], "cd"))
		cd(cmd->args, env, false); //malloc_error);
	if (ft_strcmp(cmd->args[0], "pwd"))
		pwd(STDOUT_FILENO);
	if (ft_strcmp(cmd->args[0], "export"))
		env = loop_export(env, cmd->args);
	if (ft_strcmp(cmd->args[0], "unset"))
		env = loop_unset(env, cmd->args);
	if (ft_strcmp(cmd->args[0], "env"))
		ft_env(env, STDOUT_FILENO);
	if (ft_strcmp(cmd->args[0], "exit"))
		return (0);
	return (1);
}

// Run only one command with ft_exec_cmd.

void	ft_one_cmd(t_cmd *cmd, char **env)
{
	int	pid;

	if (!is_builtin(cmd->args[0]))
	{
		pid = fork();
		if (pid == -1)
			exit_tab(cmd, 127);
		if (pid == 0)
		{
			if (!ft_exec_cmd(cmd, env))
				exit_tab(cmd, 127);
			exit_tab(cmd, 1);
		}
		wait_children(pid, cmd);
	}
	else
		ft_exec_cmd(cmd, env);
}

// Called by Pipex or ft_one_cmd.

bool	ft_exec_cmd(t_cmd *cmd, char **env)
{
	char	**paths;
	char	*line;
	int		nb_path;

	line = ft_path_line(env);
	paths = ft_split(line, ':');
	nb_path = ft_nb_path(paths);
	paths = ft_add_cmd(paths, nb_path, cmd);
	ft_open_fd(cmd);
	if (cmd->fd_infile)
	{
		printf("Marylène la truelle\n");
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(cmd->fd_infile, cmd);
	}
	if (cmd->fd_outfile)
	{
		printf("fd_outfile = %d\n", cmd->fd_outfile);
		printf("Coco le gigo\n");
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
		{
			printf("Achille le robinet\n");
			exit_fd(cmd->fd_outfile, cmd);
		}
	}
	if (is_builtin(cmd->args[0]))
	{
		if (!ft_exec_builtin(cmd, env))
			exit_tab(cmd, 127);
	}
	else if (ft_is_bin(paths, nb_path))
	{
		cmd->pathname = ft_is_bin(paths, nb_path);
		execve(cmd->pathname, cmd->args, env);
	}
	return (false);
}
