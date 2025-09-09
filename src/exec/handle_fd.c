/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:55:11 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/09 16:58:44 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "fd.h"
#include "clean.h"
#include <fcntl.h>

/*Open input redirection & check permission and existence*/
int	open_infile(t_cmd *cmd, t_mini *mini)
{
	int	fd_infile;

	fd_infile = 0;
	if (access(cmd->redir->filename, F_OK) != 0)
	{
		put_error(mini, cmd->redir->filename, "No such file or directory", 1);
		return (-1);
	}
	if (access(cmd->redir->filename, R_OK) != 0)
	{
		put_error(mini, cmd->redir->filename, "Permission denied", 1);
		return (-1);
	}
	fd_infile = open(cmd->redir->filename, O_RDONLY);
	return (fd_infile);
}

int	open_outfile(t_cmd *cmd, t_mini *mini)
{
	int	fd_outfile;

	fd_outfile = 0;
	if (cmd->redir->type == OUTPUT)
		fd_outfile = open(cmd->redir->filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (cmd->redir->type == APPEND)
		fd_outfile = open(cmd->redir->filename,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_outfile < 0)
		put_error(mini, cmd->redir->filename, "Permission denied", 1);
	return (fd_outfile);
}

int	open_redir(t_cmd *cmd, t_mini *mini)
{
	while (cmd->redir != NULL)
	{
		if (cmd->redir->type == INPUT)
		{
			cmd->fd_infile = open_infile(cmd, mini);
			if (cmd->fd_infile == -1)
				return (0);
		}
		else if (cmd->redir->type == HERE_DOC)
			cmd->fd_infile = cmd->fd_here_doc;
		else if (cmd->redir->type == OUTPUT || cmd->redir->type == APPEND)
		{
			cmd->fd_outfile = open_outfile(cmd, mini);
			if (cmd->fd_outfile == -1)
				return (0);
		}
		if (!is_close(cmd))
			return (0);
		cmd->redir = cmd->redir->next;
	}
	return (1);
}

int	ft_open_fd(t_cmd *cmd, t_mini *mini)
{
	t_redir	*temp;

	cmd->fd_infile = 0;
	cmd->fd_outfile = 1;
	if (!cmd->redir)
		return (1);
	if (cmd->fd_here_doc == -2)
		return (0);
	temp = cmd->redir;
	if (!open_redir(cmd, mini))
		return (0);
	free_redir(temp, &mini->gmalloc);
	return (1);
}

int	ft_close_fd(t_cmd *cmd, int *pipefd)
{
	if (cmd->fd_infile > 0)
		if (close(cmd->fd_infile) == -1)
			return (0);
	if (cmd->fd_outfile > 1)
		if (close(cmd->fd_outfile) == -1)
			return (0);
	if (cmd->outpipe > 0)
		if (close(cmd->outpipe) == -1)
			return (0);
	if (pipefd != 0)
	{
		if (pipefd[0] != 0)
			if (close(pipefd[0]) == -1)
				return (0);
		if (pipefd[1] != 0)
			if (close(pipefd[1]) == -1)
				return (0);
	}
	return (1);
}
