/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:50:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/28 10:12:41 by gaducurt         ###   ########.fr       */
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

int	ft_exec_builtin(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	if (ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	if (ft_strcmp(cmd->args[0], "cd"))
		cd(cmd->args, mini->env, false); //malloc_error);
	if (ft_strcmp(cmd->args[0], "pwd"))
		pwd(STDOUT_FILENO);
	if (ft_strcmp(cmd->args[0], "export"))
		mini->env = loop_export(mini->env, cmd->args, head);
	if (ft_strcmp(cmd->args[0], "unset"))
		mini->env = loop_unset(mini->env, cmd->args, head);
	if (ft_strcmp(cmd->args[0], "env"))
		ft_env(mini->env, STDOUT_FILENO);
	if (ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd->args, 0, head);
	gfree(cmd, head);
	return (1);
}

// Run only one command with ft_exec_cmd.

void	ft_one_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int	pid;

	gfree(mini->token, &mini->gmalloc);
	if (!is_builtin(cmd->args[0]))
	{
		pid = fork();
		if (pid == -1)
		{
			exit_tab(mini, 127);
			// exit_tab(cmd, 127);
		}
		if (pid == 0)
		{
			ft_open_fd(cmd);
			if (cmd->fd_infile != -1)
				if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
					exit_fd(cmd->fd_infile, mini);
					// exit_fd(cmd->fd_infile, cmd);
			if (cmd->fd_outfile != -1)
			{
				if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
					exit_fd(cmd->fd_outfile, mini);
					// exit_fd(cmd->fd_outfile, cmd);
			}
			if (!ft_exec_cmd(cmd, mini, head))
			{
				exit_tab(mini, 127);
				// exit_tab(cmd, 127);
			}
			exit_tab(mini, 1);
			// exit_tab(cmd, 1);
			ft_close_fd(cmd, 0);
		}
		wait_children(pid, cmd);
	}
	else
		ft_exec_cmd(cmd, mini, head);
}

// Called by Pipex or ft_one_cmd.

bool	ft_exec_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	char	**paths;
	char	*line;
	int		nb_path;

	line = ft_path_line(mini->env);
	paths = ft_split(line, ':');
	nb_path = ft_nb_path(paths);
	paths = ft_add_cmd(paths, nb_path, cmd);
	if (is_builtin(cmd->args[0]))
	{
		if (!ft_exec_builtin(cmd, mini, head))
		{
			// exit_tab(cmd, 127);
			exit_tab(mini, 127);
		}
	}
	else if (ft_is_bin(paths, nb_path))
	{
		// printf("c'est pas un boa ca, si ?\n");
		cmd->pathname = ft_is_bin(paths, nb_path);
		// printf("cmd->pathname = %s\n", cmd->pathname);
		execve(cmd->pathname, cmd->args, mini->env);
		// printf("arhg\n");
	}
	return (false);
}
