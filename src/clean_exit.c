/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:02:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/13 11:30:13 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_pid_error(int *pipefd, t_cmd *cmd, t_token *lst)
{
	if (pipefd[0] > 0)
		close(pipefd[0]);
	if (pipefd[1] > 0)
		close(pipefd[1]);
	if (cmd->fd_infile > 0)
		close(cmd->fd_outfile);
	if (cmd->fd_outfile > 0)
		close(cmd->fd_outfile);
	free_struct(cmd, lst);
	perror("Error");
	exit(EXIT_FAILURE);
}

void	exit_tab(t_cmd *cmd, t_token *lst, int code)
{
	free_struct(cmd, lst);
	exit(code);
}

void	exit_fd(int fd, t_cmd *cmd, t_token *lst)
{
	if (fd > 0)
		close(fd);
	free_struct(cmd, lst);
	perror(cmd->args[0]);
	exit(EXIT_FAILURE);
}
