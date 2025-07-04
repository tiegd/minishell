/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:02:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/04 10:17:27 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_pid_error(int *pipefd, t_cmd *cmd)
{
	if (pipefd[0] > 0)
		close(pipefd[0]);
	if (pipefd[1] > 0)
		close(pipefd[1]);
	if (cmd->fd_infile > 0)
		close(cmd->fd_outfile);
	if (cmd->fd_outfile > 0)
		close(cmd->fd_outfile);
	perror("Error");
	exit(EXIT_FAILURE);
}

void	exit_tab(t_cmd *cmd, int code)
{
	free_cmd(cmd);
	exit(code);
}

void	exit_fd(int fd, t_cmd *cmd)
{
	if (fd > 0)
		close(fd);
	perror(cmd->args[0]);
	exit(EXIT_FAILURE);
}

void	exit_malloc_error(t_gmalloc *head, int exit_status)
{
	perror("malloc error\n");
	gb_free_all(&head);
	exit(exit_status);
}
