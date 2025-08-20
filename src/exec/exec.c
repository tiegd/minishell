/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:50:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/20 17:32:50 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

// Check if the cmd exist with access().

char	*ft_is_bin(char **paths, int nb_path, t_cmd *cmd, t_mini *mini)
{
	int		i;

	i = 0;
	while (i <= nb_path)
	{
		if (access(paths[i], F_OK) == 0)
			return (paths[i]);
		i++;
	}
	if (errno == 14)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		exit_tab(mini, 127);
	}
	if (errno == 2)
	{
		printf("minishell: %s: No such file or directory\n", paths[0]);
		exit_tab(mini, 127);
	}
	return (NULL);
}

// Run the cmd if it's a builtin.

int	ft_exec_builtin(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	if (ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	if (ft_strcmp(cmd->args[0], "cd"))
		cd(cmd->args, mini->env, false, mini); //malloc_error);
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

	// gfree(mini->token, &mini->gmalloc);
	if (!is_builtin(cmd->args[0]))
	{
		pid = fork();
		if (pid == -1)
			exit_tab(mini, 127);
		if (pid == 0)
		{
			ft_open_fd(cmd);
			if (cmd->fd_infile != -1)
			{
				if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
					exit_fd(cmd->fd_infile, mini);
			}
			else if (cmd->fd_infile == -1)
			{
				printf("minishell: %s: No such file or directory\n", cmd->infiles->filename);
					exit_tab(mini, 127);
			}
			if (cmd->fd_outfile != -1)
				if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
					exit_fd(cmd->fd_outfile, mini);
			if (!ft_exec_cmd(cmd, mini, head))
				exit_tab(mini, 127);
			ft_close_fd(cmd, 0);
		}
		wait_children(pid, mini);
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

	if (cmd->args[0])
	{
		line = ft_path_line(mini->env, head);
		paths = gb_split(line, ':', head);
		nb_path = ft_nb_path(paths);
		paths = ft_add_cmd(paths, nb_path, cmd, head);
		manage_error_exec(cmd, mini, paths);
		if (is_builtin(cmd->args[0]))
		{
			if (!ft_exec_builtin(cmd, mini, head))
				exit_tab(mini, 127);
		}
		else if (ft_is_bin(paths, nb_path, cmd, mini))
		{
			cmd->pathname = ft_is_bin(paths, nb_path, cmd, mini);
			if (!execve(cmd->pathname, cmd->args, mini->env))
				exit_tab(mini, 127);
		}
	}
	return (false);
}
