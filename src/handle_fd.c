/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:55:11 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/18 15:39:35 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_init_fd(t_token *lst)
// {
// 	t_token	*tmp;

// 	tmp = lst;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->type == INPUT || tmp->type == OUTPUT || tmp->type == APPEND)
// 		{
// 			tmp = tmp->next;
// 			tmp->type = FD;
// 		}
// 		tmp = tmp->next;
// 	}
// }

int	ft_open_infile(t_cmd *cmd)
{
	while (cmd->infiles->next)
	{
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
	return (cmd->fd_infile);
}

int	ft_open_outfile(t_cmd *cmd)
{
	while (cmd->outfiles->next)
	{
		cmd->fd_outfile = open(cmd->outfiles->filename, O_RDONLY | O_CREAT | O_TRUNC, 0666);
		if (cmd->fd_outfile < 0)
			return (0);
		if (cmd->outfiles->next != NULL)
		{
			if (close(cmd->fd_outfile) == -1)
				return (0);
		}
		cmd->outfiles = cmd->outfiles->next;
	}
	return (cmd->fd_outfile);
}

// int	ft_open_fd(t_cmd *cmd)
// {
// 	if (cmd->infiles)
// 	{
// 		while (cmd->infiles->next)
// 		{
// 			cmd->fd_infile = open(cmd->infiles->filename, O_RDONLY);
// 			if (cmd->fd_infile < 0)
// 				return (0);
// 			if (cmd->infiles->next != NULL)
// 			{
// 				if (close(cmd->fd_infile) == -1)
// 					return (0);
// 			}
// 			cmd->infiles = cmd->infiles->next;
// 		}
// 	}
// 	if (cmd->outfiles)
// 	{
// 		while (cmd->outfiles->next)
// 		{
// 			cmd->fd_outfile = open(cmd->outfiles->filename, O_RDONLY | O_CREAT | O_TRUNC, 0666);
// 			if (cmd->fd_outfile < 0)
// 				return (0);
// 			if (cmd->outfiles->next != NULL)
// 			{
// 				if (close(cmd->fd_outfile) == -1)
// 					return (0);
// 			}
// 			cmd->outfiles = cmd->outfiles->next;
// 		}
// 	}
// 	return (1);
// }

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
	return (1);
}
