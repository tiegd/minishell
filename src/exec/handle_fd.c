/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:55:11 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/01 14:21:56 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_infile(t_cmd *cmd, t_mini *mini)
{
	(void)mini;
	if (cmd->infiles == NULL)
	{
		cmd->fd_infile = 0;
		return (1);
	}
	while (cmd->infiles != NULL)
	{
		if (access(cmd->infiles->filename, F_OK) != 0)
		{
			put_error(mini, cmd->infiles->filename, "No such file or directory", 1);
			return (0);
		}
		cmd->fd_infile = open(cmd->infiles->filename, O_RDONLY);
		if (cmd->fd_infile < 0)
			return (0);
		if (cmd->infiles->next != NULL)
		{
			if (close(cmd->fd_infile) == -1)
				return (0);
		}
		cmd->infiles = cmd->infiles->next;
	}
	return (1);
}

void	ft_open_outfile(t_cmd *cmd)
{
	if (cmd->outfiles == NULL)
		cmd->fd_outfile = 1;
	while (cmd->outfiles != NULL)
	{
		if (cmd->outfiles->type == OUTPUT)
			cmd->fd_outfile = open(cmd->outfiles->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (cmd->outfiles->type == APPEND)
			cmd->fd_outfile = open(cmd->outfiles->filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (cmd->fd_outfile < 0)
		{
			// cmd->outfile_name = ft_strdup(cmd->outfiles->filename);
			return ;
		}
		if (cmd->outfiles->next != NULL)
		{
			if (close(cmd->fd_outfile) == -1)
				return ;
		}
		cmd->outfiles = cmd->outfiles->next;
	}
}

int	ft_open_fd(t_cmd *cmd, t_mini *mini)
{
	cmd->fd_infile = 0;
	cmd->fd_outfile = 1;
	ft_open_outfile(cmd);
	if (cmd->fd_here_doc != 0)
	{
		cmd->fd_infile = cmd->fd_here_doc;
		return (1);
	}
	if (ft_open_infile(cmd, mini) == 0)
		return (0);
	return (1);
}

// int	ft_open_fd(t_cmd *cmd, t_mini *mini)
// {
// 	cmd->fd_infile = 0;
// 	cmd->fd_outfile = 1;
// 	if (ft_open_infile(cmd, mini) == 0)
// 	{
// 		ft_open_outfile(cmd);
// 		return (1);
// 	}
// 	else
// 		return (0);
// 	if (cmd->fd_here_doc != 0)
// 	{
// 		cmd->fd_infile = cmd->fd_here_doc;
// 		return (1);
// 	}
// 	return (1);
// }

int	ft_close_fd(t_cmd *cmd, int *pipefd)
{
	printf(GREEN"pipefd[0] = %d;\npipefd[1] = %d\n"RESET, pipefd[0], pipefd[1]);
	if (cmd->fd_infile != 0)
	{
		if (close(cmd->fd_infile) == -1)
			return (0);
	}
	if (cmd->fd_outfile != 0)
	{
		if (close(cmd->fd_outfile) == -1)
			return (0);
	}
	if (pipefd != 0)
	{
		if (pipefd[0] != 0 )
		{
			if (close(pipefd[0]) == -1)
			return (0);
		}
		if (pipefd[1] != 0)
		{
			if (close(pipefd[1]) == -1)
			return (0);
		}
	}
	return (1);
}
