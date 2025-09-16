/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:57:23 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/16 16:36:48 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean.h"
#include "exec.h"

#include <stdio.h>

// Do redir if we have an infile or outfile.

void	redir_one(t_cmd *cmd, t_mini *mini)
{
	if (cmd->fd_infile != -1 && cmd->fd_infile != 0)
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

void	one_no_fork(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	mini->dup_std[0] = dup(STDIN_FILENO);
	mini->dup_std[1] = dup(STDOUT_FILENO);
	redir_one(cmd, mini);
	ft_exec_cmd(cmd, mini, head, -1);
}

void	redir_first_pipe(t_mini *mini, t_cmd *cmd, int *pipefd)
{
	if (cmd->fd_infile != -1 && cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(cmd, mini, pipefd);
	}
	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 1)
	{
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
			exit_fd(cmd, mini, pipefd);
	}
	else
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit_fd(cmd, mini, pipefd);
	}
}

void	redir_middle_pipe(t_mini *mini, t_cmd *cmd, int *pipefd)
{
	if (cmd->fd_infile != -1 && cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(cmd, mini, pipefd);
	}
	else
		if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
			exit_fd(cmd, mini, pipefd);
	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 1)
	{
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
			exit_fd(cmd, mini, pipefd);
	}
	else
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit_fd(cmd, mini, pipefd);
}

void	redir_last_pipe(t_mini *mini, t_cmd *cmd, int *pipefd)
{
	if (cmd->fd_infile != -1 && cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(cmd, mini, pipefd);
	}
	else
	{
		if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
			exit_fd(cmd, mini, pipefd);
	}
	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 1)
	{
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
			exit_fd(cmd, mini, pipefd);
	}
}
