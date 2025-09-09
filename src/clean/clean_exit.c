/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:02:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/09 08:25:28 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	exit_tab(t_cmd *cmd, t_mini *mini, int code, int *pipefd)
{
	ft_close_fd(cmd, pipefd);
	gb_free_all(&mini->gmalloc);
	rl_clear_history();
	exit(code);
}

void	exit_fd(t_cmd *cmd, t_mini *mini, int *pipefd)
{
	ft_close_fd(cmd, pipefd);
	gb_free_all(&mini->gmalloc);
	mini->exit_status = 1;
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	exit_malloc_error(t_gmalloc *head, int exit_status)
{
	perror("malloc error\n");
	gb_free_all(&head);
	rl_clear_history();
	exit(exit_status);
}

int	str_return(char *str, int exit_status, t_mini *mini)
{
	ft_putstr_fd(str, 2);
	mini->exit_status = exit_status;
	return (0);
}
