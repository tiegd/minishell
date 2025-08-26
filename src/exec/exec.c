/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:50:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/26 12:00:34 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

// Check if the cmd exist with access().

char	*ft_is_bin(t_cmd *cmd, t_mini *mini)
{
	int		i;

	i = 0;
	while (cmd->paths[i] != NULL)
	{
		// printf("cmd->paths[%d] = %s\n", i, cmd->paths[i]);
		if (access(cmd->paths[i], F_OK) == 0)
			return (cmd->paths[i]);
		i++;
	}
	printf("errno = %d\n", errno);
	if (errno == 2)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		// exit_tab(mini, 127);
		mini->exit_status = 127;
	}
	// if (errno == 2)
	// {
	// 	printf("minishell: %s: No such file or directory\n", cmd->paths[0]);
	// 	// exit_tab(mini, 127);
	// 	mini->exit_status = 127;
	// }
	return (NULL);
}

// Run the cmd if it's a builtin.

int	ft_exec_builtin(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	if (ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	if (ft_strcmp(cmd->args[0], "cd"))
		cd(cmd->args, mini->env, head, mini); //malloc_error);
	if (ft_strcmp(cmd->args[0], "pwd"))
		pwd(STDOUT_FILENO);
	if (ft_strcmp(cmd->args[0], "export") && !cmd->args[1])
		print_export(mini->env, head);
	if (ft_strcmp(cmd->args[0], "export"))
		mini->env = loop_export(mini->env, cmd->args, head);
	if (ft_strcmp(cmd->args[0], "unset"))
		mini->env = loop_unset(mini->env, cmd->args, head);
	if (ft_strcmp(cmd->args[0], "env"))
		ft_env(mini->env, STDOUT_FILENO);
	if (ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd->args, 0, head);
	dup2(STDIN_FILENO, 0);
	dup2(STDOUT_FILENO, 1);
	gfree(cmd, head);
	return (1);
}

void	ft_redir(t_cmd *cmd, t_mini *mini)
{
	ft_open_fd(cmd);
	if (cmd->fd_infile != -1 &&  cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(cmd->fd_infile, mini);
	}
	else if (cmd->fd_infile == -1)
	{
		printf("minishell: %s: No such file or directory\n", cmd->infiles->filename);
		exit_tab(mini, 1);
	}
	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 1)
	{
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
			exit_fd(cmd->fd_outfile, mini);
	}
	else if (cmd->fd_outfile == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd->infiles->filename);
		exit_tab(mini, 1);
	}
}
// Restore stdin and stdout.

void	ft_dup_out(t_cmd *cmd, int *dup_std)
{
	if (cmd->fd_infile != 0)
		dup2(dup_std[0], STDIN_FILENO);
	if (cmd->fd_outfile != 1)
		dup2(dup_std[1], STDOUT_FILENO);
}

// Extract the $PATH in env to a char**.

void extract_path(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	char	*line;
	int		nb_path;
	
	line = ft_path_line(mini->env, head);
	cmd->paths = gb_split(line, ':', head);
	nb_path = ft_nb_path(cmd->paths);
	cmd->paths = ft_add_cmd(cmd->paths, nb_path, mini->cmd, head);
	manage_error_exec(mini->cmd, mini, cmd->paths);
}

// Run only one command with ft_exec_cmd.

void	ft_one_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int		pid;
	int		dup_std[2];

	extract_path(cmd, mini, head);
	if (ft_is_bin(cmd, mini))
	{
		pid = fork();
		if (pid == -1)
			exit_tab(mini, 127);
		if (pid == 0)
		{
			ft_redir(cmd, mini);
			if (!ft_exec_cmd(cmd, mini, head))
				exit_tab(mini, 127);
			ft_close_fd(cmd, 0);
		}
		wait_children(pid, mini);
	}
	else
	{
		dup_std[0] = dup(STDIN_FILENO);
		dup_std[1] = dup(STDOUT_FILENO);
		ft_redir(cmd, mini);
		ft_exec_cmd(cmd, mini, head);
		ft_dup_out(cmd, dup_std);
	}
}

// Called by Pipex or ft_one_cmd.

bool	ft_exec_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	if (cmd->args[0])
	{
		if (is_builtin(cmd->args[0]))
		{
			if (!ft_exec_builtin(cmd, mini, head))
				return (false);
		}
		else if (ft_is_bin(cmd, mini))
		{
			cmd->pathname = ft_is_bin(cmd, mini);
			if (!execve(cmd->pathname, cmd->args, mini->env))
				return (false);
		}
	}
	return (true);
}
