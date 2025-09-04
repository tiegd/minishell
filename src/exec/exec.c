/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:50:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/04 22:47:49 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

// Run the cmd if it's a builtin.
int	ft_exec_builtin(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	if (ft_strcmp(cmd->args[0], "echo"))
	{
		ft_echo(cmd);
		mini->exit_status = 0;
	}
	if (ft_strcmp(cmd->args[0], "cd"))
		cd(cmd->args, mini->env, head, mini);
	if (ft_strcmp(cmd->args[0], "pwd"))
		pwd(STDOUT_FILENO, mini);
	if (ft_strcmp(cmd->args[0], "export") && !cmd->args[1])
		print_export(mini->env, mini, head);
	if (ft_strcmp(cmd->args[0], "export"))
		mini->env = loop_export(mini->env, cmd->args, mini, head);
	if (ft_strcmp(cmd->args[0], "unset"))
		mini->env = loop_unset(mini->env, cmd->args, mini, head);
	if (ft_strcmp(cmd->args[0], "env"))
		ft_env(mini->env, STDOUT_FILENO, mini);
	if (ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd->args, mini, head);
	close_fds(cmd->fd_infile, cmd->fd_outfile);
	gfree(cmd, head);
	return (1);
}

// Restore stdin and stdout.

void	ft_dup_out(t_mini *mini)
{
	dup2(mini->dup_std[0], STDIN_FILENO);
	dup2(mini->dup_std[1], STDOUT_FILENO);
	close(mini->dup_std[0]);
	close(mini->dup_std[1]);
}

void	launch_one_child(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	redir_one(cmd, mini);
	close_fds(cmd->fd_infile, cmd->fd_outfile);
	if (!ft_exec_cmd(cmd, mini, head))
		exit_tab(cmd, mini, 127, 0);
}

// Run only one command with ft_exec_cmd.
void	ft_one_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int		pid;

	if (!ft_open_fd(cmd, mini))
	{
		ft_close_fd(cmd, 0);
		return ;
	}
	if (!is_builtin(cmd->args[0]))
	{
		if (!check_cmd(cmd, mini, head))
			return ;
		pid = fork();
		if (pid == -1)
			exit_tab(cmd, mini, 127, 0);
		if (pid == 0)
			launch_one_child(cmd, mini, head);
		wait_children(pid, mini);
		close_fds(cmd->fd_infile, cmd->fd_outfile);
		if (sig_flag != 0)
			write(STDOUT_FILENO, "\n", 1);
	}
	else
		one_no_fork(cmd, mini, head);
}

// Called by Pipex or ft_one_cmd.
bool	ft_exec_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	if (is_builtin(cmd->args[0]))
	{
		if (!ft_exec_builtin(cmd, mini, head))
			return (false);
		ft_dup_out(mini);
	}
	else if (!is_builtin(cmd->args[0]))
	{
		execve(cmd->pathname, cmd->args, mini->env);
		put_error(mini, cmd->args[0], "Command not found", 127);
		exit(127);
	}
	if (mini->nb_pipe > 0)
		exit(0);
	return (true);
}
