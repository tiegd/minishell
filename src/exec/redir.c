/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:57:23 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/04 13:57:42 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
