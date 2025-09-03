/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:50:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/03 10:40:07 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

// // Check if the cmd exist with access().
// int	ft_is_bin(t_cmd *cmd, t_mini *mini)
// {
// 	int		i;

// 	i = 0;
// 	cmd->pathname = NULL;
// 	if (cmd->args[0][0] == '.')
// 		return (0);
// 	while (ft_strchr(cmd->args[0], '/') && cmd->paths[i] != NULL)
// 	{
// 		if (access(cmd->paths[i], F_OK) == 0)
// 		{
// 			cmd->pathname = cmd->paths[i];
// 			return (1);
// 		}
// 		i++;
// 	}
// 	printf("errno = %d\n", errno);
// 	if (errno == 2 && mini->nb_pipe == 0)
// 	{
// 		if (cmd->args[0][0] == '/' && access(cmd->args[0], F_OK) != 0)
// 		{
// 			put_error(mini, cmd->args[0], "No such file or directory", 127);
// 			return (0);
// 		}
// 		else if (cmd->args[0][0] != '/')
// 		{
// 			put_error(mini, cmd->args[0], "command not found", 127);
// 			return (0);
// 		}
// 	}
// 	return (0);
// }

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
		ft_exit(cmd->args, mini, head);
	close_fds(cmd->fd_infile, cmd->fd_outfile);
	gfree(cmd, head);
	return (1);
}

// Do redir if we have an infile or outfile.
void	redir_one(t_cmd *cmd, t_mini *mini)
{
	if (cmd->fd_infile != -1 &&  cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(cmd, mini, 0);
	}
	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 1)
	{
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
			exit_fd(cmd, mini, 0);
	}
}
// // Do redir if we have an infile or outfile.
// void	redir_one(t_cmd *cmd, t_mini *mini)
// {
// 	if (cmd->fd_infile != -1 &&  cmd->fd_infile != 0)
// 	{
// 		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
// 			exit_fd(cmd->fd_infile, mini);
// 	}
// 	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 1)
// 	{
// 		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
// 			exit_fd(cmd->fd_outfile, mini);
// 	}
// }

// // Do redir if we have an infile or outfile.
// void	redir_one(t_cmd *cmd, t_mini *mini)
// {
// 	if (cmd->fd_infile != -1 &&  cmd->fd_infile != 0)
// 	{
// 		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
// 			exit_fd(cmd->fd_infile, mini);
// 	}
// 	else if (cmd->fd_infile == -1)
// 	{
// 		put_error(mini, cmd->infiles->filename, "Permission denied", 1);
// 		if (!is_builtin(cmd->args[0]))
// 			exit_tab(mini, 1);
// 	}
// 	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 1)
// 	{
// 		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
// 			exit_fd(cmd->fd_outfile, mini);
// 	}
// 	else if (cmd->fd_outfile == -1)
// 	{
// 		put_error(mini, cmd->outfiles->filename, "Permission denied", 1);
// 		if (!is_builtin(cmd->args[0]))
// 			exit_tab(mini, 1);
// 	}
// }

// Restore stdin and stdout.

void	ft_dup_out(t_mini *mini)
{
	dup2(mini->dup_std[0], STDIN_FILENO);
	dup2(mini->dup_std[1], STDOUT_FILENO);
	close(mini->dup_std[0]);
	close(mini->dup_std[1]);
}

// Run only one command with ft_exec_cmd.
void	ft_one_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int		pid;

	if (!ft_open_fd(cmd, mini))
		return ;	
	if (!is_builtin(cmd->args[0]))
	{
		if (!check_cmd(cmd, mini, head))
			return ;
		pid = fork();
		if (pid == -1)
			exit_tab(mini, 127, 0);
		if (pid == 0)
		{
			redir_one(cmd, mini);
			close_fds(cmd->fd_infile, cmd->fd_outfile);
			if (!ft_exec_cmd(cmd, mini, head))
				exit_tab(mini, 127, 0);
		}
		wait_children(pid, mini);
		close_fds(cmd->fd_infile, cmd->fd_outfile);
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
		ft_dup_out(mini);
	}
	else if (!is_builtin(cmd->args[0]))
	{
		execve(cmd->pathname, cmd->args, mini->env);
		exit(127);
	}
	if (mini->nb_pipe > 0)
		exit(0);
	return (true);
}
