/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/22 09:19:35 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Run the first command and redirect the output to the following command.

static void	first_pipe(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int	pid;
	int	pipefd[2];

	if(pipe(pipefd) == -1)
		exit_tab(cmd, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit_pid_error(pipefd, cmd);
	if (pid == 0)
	{
		ft_open_fd(cmd);
		if (cmd->fd_infile != -1)
			if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
				exit_fd(cmd->fd_infile, cmd);
		if (cmd->fd_outfile != -1)
		{
			if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
				exit_fd(cmd->fd_outfile, cmd);
		}
		else
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit_fd(pipefd[1], cmd);
		close(pipefd[0]);
		close(pipefd[1]);
		print_tab_char(cmd->args);
		if (!ft_exec_cmd(cmd, mini, head))
		{
			// printf("100 - 8 zoo\n");
			ft_close_fd(cmd, pipefd);
			exit_tab(cmd, 127);
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
		exit_tab(cmd, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit_pid_error(pipefd, cmd);
	if (pid == 0)
	{
		ft_open_fd(cmd);
		if (cmd->fd_infile != -1)
		{
			if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
				exit_fd(cmd->fd_infile, cmd);
		}
		else
			if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
				exit_fd(cmd->outpipe, cmd);
		if (cmd->fd_outfile != -1)
		{
			if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
				exit_fd(cmd->fd_outfile, cmd);
		}
		else
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit_fd(pipefd[1], cmd);
		close(pipefd[0]);
		close(pipefd[1]);
		if (!ft_exec_cmd(cmd, mini, head))
		{
			ft_close_fd(cmd, pipefd);
			exit_tab(cmd, 127);
		}
	}
	close(pipefd[1]);
	cmd->outpipe = pipefd[0];
}

// Run the the command and redirect the output to the terminal.

static void	last_pipe(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int	pid_last;

	pid_last = fork();
	if (pid_last == -1)
		exit_tab(cmd, EXIT_FAILURE);
	if (pid_last == 0)
	{
		ft_open_fd(cmd);
		if (cmd->fd_infile != -1)
		{
			// printf("gontran pichard\n");
			if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
				exit_fd(cmd->fd_infile, cmd);
		}
		else
		{
			// printf("gaetan le singe, artiste 2 rue\n");
			if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
				exit_fd(cmd->outpipe, cmd);
		}
		if (cmd->fd_outfile != -1)
		{
			// printf("thierry pelouse\n");
			if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
				exit_fd(cmd->fd_outfile, cmd);
		}
		// print_tab_char(cmd->args);
		if (!ft_exec_cmd(cmd, mini, head))
		{
			// printf("theo porose, con\n");
			ft_close_fd(cmd, 0);
			exit_tab(cmd, 127);
		}
		// exit_tab(cmd, 1);
		close(cmd->outpipe);
	}
	close(cmd->outpipe);
	wait_children(pid_last, cmd);
}

// This function shall reproduce the behavior of '|' in bash.

void	pipex(t_cmd *cmd, t_mini *mini, int nb_pipe, t_gmalloc **head)
{
	int	i;

	i = 0;
	while (i <= nb_pipe)
	{
		if (i == 0)
			first_pipe(cmd, mini, head);
		else if (i == nb_pipe)
			last_pipe(cmd, mini, head);
		else
			middle_pipe(cmd, mini, head);
		if (i < nb_pipe)
			cmd->next->outpipe = cmd->outpipe;
		i++;
		cmd = cmd->next;
	}
}
