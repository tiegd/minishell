/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:50:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/28 18:08:06 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

// Check if the cmd exist with access().

void	ft_is_bin(t_cmd *cmd, t_mini *mini)
{
	int		i;

	i = 0;
	cmd->pathname = NULL;
	while (cmd->paths[i] != NULL)
	{
		if (access(cmd->paths[i], F_OK) == 0)
		{
			cmd->pathname = cmd->paths[i];
			return;
		}
		i++;
	}
	// if (errno == 2 && cmd->fd_infile != -1)
	if (errno == 2 && cmd->error == 1)//ft_open_infile(cmd, mini) == 1)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		mini->exit_status = 127;
	}
	return;
}

// Run the cmd if it's a builtin.

int	ft_exec_builtin(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	if (ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	if (ft_strcmp(cmd->args[0], "cd"))
		cd(cmd->args, mini->env, head, mini); //malloc_error);
	if (ft_strcmp(cmd->args[0], "pwd"))
		pwd(STDOUT_FILENO, mini);
	if (ft_strcmp(cmd->args[0], "export") && !cmd->args[1])
		print_export(mini->env, head);
	if (ft_strcmp(cmd->args[0], "export"))
		mini->env = loop_export(mini->env, cmd->args, mini, head);
	if (ft_strcmp(cmd->args[0], "unset"))
		mini->env = loop_unset(mini->env, cmd->args, head);
	if (ft_strcmp(cmd->args[0], "env"))
		ft_env(mini->env, STDOUT_FILENO);
	if (ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd->args, 0, head);
	gfree(cmd, head);
	return (1);
}

void	redir_one(t_cmd *cmd, t_mini *mini)
{
	// ft_open_fd(cmd, mini);
	if (cmd->fd_infile != -1 &&  cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(cmd->fd_infile, mini);
	}
	else if (cmd->fd_infile == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd->infiles->filename);
		if (!is_builtin(cmd->args[0]))
			exit_tab(mini, 1);
		mini->exit_status = 1;
	}
	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 1)
	{

		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
			exit_fd(cmd->fd_outfile, mini);
	}
	else if (cmd->fd_outfile == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd->outfiles->filename);
		if (!is_builtin(cmd->args[0]))
			exit_tab(mini, 1);
		mini->exit_status = 1;
	}
}
// Restore stdin and stdout.

void	ft_dup_out(t_cmd *cmd, t_mini *mini)
{
	if (cmd->fd_infile != 0)
		dup2(mini->dup_std[0], STDIN_FILENO);
	if (cmd->fd_outfile != 1)
		dup2(mini->dup_std[1], STDOUT_FILENO);
}

// Extract the $PATH in env to a char**.

void extract_path(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	char	*line;
	int		nb_path;

	line = ft_path_line(mini->env, head);
	cmd->paths = gb_split(line, ':', head);
	nb_path = ft_nb_path(cmd->paths);
	if (cmd->args[0])
	{
		cmd->paths = ft_add_cmd(cmd->paths, nb_path, cmd, head);
		manage_error_exec(mini->cmd, mini, cmd->paths);
	}
}

// Run only one command with ft_exec_cmd.
void	ft_one_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int		pid;

	// if (!ft_open_infile(cmd, mini))
	if (!ft_open_fd(cmd, mini))
		return ;
	extract_path(cmd, mini, head);
	if (!is_builtin(cmd->args[0]))
	{
		ft_is_bin(cmd, mini);
		pid = fork();
		if (pid == -1)
			exit_tab(mini, 127);
		if (pid == 0)
		{
			redir_one(cmd, mini);
			if (!ft_exec_cmd(cmd, mini, head))
				exit_tab(mini, 127);
			ft_close_fd(cmd, 0);
		}
		wait_children(pid, mini);
		if (sig_flag != 0)
			write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		mini->dup_std[0] = dup(STDIN_FILENO);
		mini->dup_std[1] = dup(STDOUT_FILENO);
		redir_one(cmd, mini);
		ft_exec_cmd(cmd, mini, head);
	}
}

// Called by Pipex or ft_one_cmd.
bool	ft_exec_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	if (is_builtin(cmd->args[0]))
	{
		if (!ft_exec_builtin(cmd, mini, head))
			return (false);
		ft_dup_out(cmd, mini);
		mini->exit_status = 0;
	}
	else if (!is_builtin(cmd->args[0]) && access(cmd->pathname, F_OK) == 0)
	{
		execve(cmd->pathname, cmd->args, mini->env);
	}
	if (mini->nb_pipe > 0)
		exit(0);
	return (true);
}
