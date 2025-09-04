/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/04 23:46:10 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Run the first command and redirect the output to the following command.

static void	first_pipe(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		exit_tab(cmd, mini, EXIT_FAILURE, pipefd);
	pid = fork();
	if (pid == -1)
		exit_pid_error(pipefd, mini);
	if (pid == 0)
	{
		if (!ft_open_fd(cmd, mini))
			exit_tab(cmd, mini, 1, pipefd);
		if (!check_cmd(cmd, mini, head))
			exit_tab(cmd, mini, mini->exit_status, pipefd);
		redir_first_pipe(mini, cmd, pipefd);
		ft_close_fd(cmd, pipefd);
		if (!ft_exec_cmd(cmd, mini, head))
		{
			ft_close_fd(cmd, pipefd);
			exit_tab(cmd, mini, 127, pipefd);
		}
	}
	close(pipefd[1]);
	cmd->outpipe = pipefd[0];
}

// Run a middle command and redirect the output to the following command.

static void	middle_pipe(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		exit_tab(cmd, mini, EXIT_FAILURE, pipefd);
	pid = fork();
	if (pid == -1)
		exit_pid_error(pipefd, mini);
	if (pid == 0)
	{
		if (!ft_open_fd(cmd, mini))
			exit_tab(cmd, mini, 1, pipefd);
		if (!check_cmd(cmd, mini, head))
			exit_tab(cmd, mini, mini->exit_status, pipefd);
		redir_middle_pipe(mini, cmd, pipefd);
		ft_close_fd(cmd, pipefd);
		if (!ft_exec_cmd(cmd, mini, head))
		{
			ft_close_fd(cmd, pipefd);
			exit_tab(cmd, mini, 127, pipefd);
		}
	}
	close(pipefd[1]);
	close(cmd->outpipe);
	cmd->outpipe = pipefd[0];
}

// Run the the command and redirect the output to the terminal.

static void	last_pipe(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int	pid_last;

	pid_last = fork();
	if (pid_last == -1)
		exit_tab(cmd, mini, EXIT_FAILURE, 0);
	if (pid_last == 0)
	{
		if (!ft_open_fd(cmd, mini))
			exit_tab(cmd, mini, 1, 0);
		if (!check_cmd(cmd, mini, head))
			exit_tab(cmd, mini, mini->exit_status, 0);
		redir_last_pipe(mini, cmd, 0);
		ft_close_fd(cmd, 0);
		if (!ft_exec_cmd(cmd, mini, head))
		{
			ft_close_fd(cmd, 0);
			exit_tab(cmd, mini, 127, 0);
		}
	}
	close(cmd->outpipe);
	wait_children(pid_last, mini);
}

// This function shall reproduce the behavior of '|' in bash.

void	pipex(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int	i;

	i = 0;
	cmd->outpipe = 0;
	while (cmd)
	{
		if (i == 0)
			first_pipe(cmd, mini, head);
		else if (i == mini->nb_pipe)
			last_pipe(cmd, mini, head);
		else
			middle_pipe(cmd, mini, head);
		if (i < mini->nb_pipe)
			cmd->next->outpipe = cmd->outpipe;
		close_fds(cmd->fd_infile, cmd->fd_outfile);
		i++;
		cmd = cmd->next;
	}
	if (sig_flag != 0)
		write(STDOUT_FILENO, "\n", 1);
}
