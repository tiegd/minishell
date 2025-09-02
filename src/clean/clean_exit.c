/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:02:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/02 10:18:38 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exit_pid_error(int *pipefd, t_cmd *cmd)
// {
// 	if (pipefd[0] > 0)
// 		close(pipefd[0]);
// 	if (pipefd[1] > 0)
// 		close(pipefd[1]);
// 	if (cmd->fd_infile > 0)
// 		close(cmd->fd_outfile);
// 	if (cmd->fd_outfile > 0)
// 		close(cmd->fd_outfile);
// 	perror("Error");
// 	exit(EXIT_FAILURE);
// }

void	exit_pid_error(int *pipefd, t_mini *mini)
{
	if (pipefd[0] > 0)
		close(pipefd[0]);
	if (pipefd[1] > 0)
		close(pipefd[1]);
	if (mini->cmd->fd_infile > 0)
		close(mini->cmd->fd_outfile);
	if (mini->cmd->fd_outfile > 0)
		close(mini->cmd->fd_outfile);
	gb_free_all(&mini->gmalloc);
	perror("Error");
	exit(EXIT_FAILURE);
}

// void	exit_tab(t_cmd *cmd, int code)
// {
// 	(void)cmd;
// 	// free_cmd(cmd, head);
// 	exit(code);
// }

void	exit_tab(t_mini *mini, int code, int *pipefd)
{
	ft_close_fd(mini->cmd, pipefd);
	gb_free_all(&mini->gmalloc);
	exit(code);
}

void	exit_fd(int fd, t_mini *mini)
{
	if (fd > 0)
		close(fd);
	gb_free_all(&mini->gmalloc);
	mini->exit_status = 1;
	exit(EXIT_FAILURE);
}

void	exit_malloc_error(t_gmalloc *head, int exit_status)
{
	perror("malloc error\n");
	gb_free_all(&head);
	exit(exit_status);
}

int	str_return(const char *str, int exit_status, t_mini *mini)
{
	printf("%s", str);
	mini->exit_status = exit_status;
	return(0);
}
