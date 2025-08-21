/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:55:11 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/21 17:27:15 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_infile(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	if (cmd->infiles == NULL)
		cmd->fd_infile = 0;
	while (cmd->infiles != NULL)
	{
		if (cmd->infiles->type == HERE_DOC)
			cmd->fd_infile = here_doc(mini, cmd->infiles->filename, head);
		else
			cmd->fd_infile = open(cmd->infiles->filename, O_RDONLY);
		if (cmd->fd_infile < 0)
			return ;
		if (cmd->infiles->next != NULL)
		{
			if (close(cmd->fd_infile) == -1)
				return ;
		}
		cmd->infiles = cmd->infiles->next;
	}
}

void	ft_open_outfile(t_cmd *cmd)
{
	if (cmd->outfiles == NULL)
		cmd->fd_outfile = -1;
	while (cmd->outfiles != NULL)
	{
		if (cmd->outfiles->type == OUTPUT)
			cmd->fd_outfile = open(cmd->outfiles->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (cmd->outfiles->type == APPEND)
			cmd->fd_outfile = open(cmd->outfiles->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (cmd->fd_outfile < 0)
			return ;
		if (cmd->outfiles->next != NULL)
		{
			if (close(cmd->fd_outfile) == -1)
				return ;
		}
		cmd->outfiles = cmd->outfiles->next;
	}
}

void	ft_open_fd(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	cmd->fd_infile = 0;
	cmd->fd_outfile = 0;
	ft_open_infile(cmd, mini, head);
	ft_open_outfile(cmd);
}

// void	ft_fd_to_pipe(t_cmd *cmd)
// {
// 	ft_open_fd(cmd);
// 	if (cmd->fd_infile != -1)
// 	{
// 		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
// 			exit_fd(cmd->fd_infile, cmd);
// 	}
// 	if (cmd->fd_outfile != -1)
// 	{
// 		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
// 			exit_fd(cmd->fd_outfile, cmd);
// 	}
// }

void	ft_fd_to_pipe(t_mini *mini)
{
	ft_open_fd(mini->cmd, mini, &mini->gmalloc);
	if (mini->cmd->fd_infile != -1)
	{
		if (dup2(mini->cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(mini->cmd->fd_infile, mini);
	}
	if (mini->cmd->fd_outfile != -1)
	{
		if (dup2(mini->cmd->fd_outfile, STDOUT_FILENO) == -1)
			exit_fd(mini->cmd->fd_outfile, mini);
	}
}

int	ft_close_fd(t_cmd *cmd, int *pipefd)
{
	if (cmd->fd_infile >= 0)
	{
		if (close(cmd->fd_infile) == -1)
			return (0);
	}
	if (cmd->fd_outfile >= 0)
	{
		if (close(cmd->fd_outfile) == -1)
			return (0);
	}
	if (pipefd != 0)
	{
		if (pipefd[0] >= 0 )
		{
			if (close(pipefd[0]) == -1)
			return (0);
		}
		if (pipefd[1] >= 0)
		{
			if (close(pipefd[1]) == -1)
			return (0);
		}
	}
	return (1);
}
