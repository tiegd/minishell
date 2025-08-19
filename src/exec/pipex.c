/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/19 14:08:33 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Run the first command and redirect the output to the following command.

static void	first_pipe(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	int	pid;
	int	pipefd[2];

	if(pipe(pipefd) == -1)
		exit_tab(mini, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit_pid_error(pipefd, mini);
	if (pid == 0)
	{
		ft_open_fd(cmd);
		if (cmd->fd_infile != -1)
		{
			if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
				exit_fd(cmd->fd_infile, mini);
		}
		else
		{
			printf("minishell: %s: No such file or directory\n", cmd->infiles->filename);
			exit_tab(mini, 127);
		}
		if (cmd->fd_outfile != -1)
		{
			if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
				exit_fd(cmd->fd_outfile, mini);
		}
		else
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit_fd(pipefd[1], mini);
		close(pipefd[0]);
		close(pipefd[1]);
		if (!ft_exec_cmd(cmd, mini, head))
		{
			ft_close_fd(cmd, pipefd);
			exit_tab(mini, 127);
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
		exit_tab(mini, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit_pid_error(pipefd, mini);
	if (pid == 0)
	{
		ft_open_fd(cmd);
		if (cmd->fd_infile != -1)
		{
			if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
				exit_fd(cmd->fd_infile, mini);
		}
		else if (cmd->fd_infile == -1)
		{
			printf("minishell: %s: No such file or directory\n", cmd->infiles->filename);
			exit_tab(mini, 127);
		}
		else
			if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
				exit_fd(cmd->outpipe, mini);
		if (cmd->fd_outfile != -1)
		{
			if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
				exit_fd(cmd->fd_outfile, mini);
		}
		else
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit_fd(pipefd[1], mini);
		close(pipefd[0]);
		close(pipefd[1]);
		if (!ft_exec_cmd(cmd, mini, head))
		{
			ft_close_fd(cmd, pipefd);
			exit_tab(mini, 127);
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
		exit_tab(mini, EXIT_FAILURE);
	if (pid_last == 0)
	{
		ft_open_fd(cmd);
		if (cmd->fd_infile != -1)
		{
			if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
				exit_fd(cmd->fd_infile, mini);
		}
		else if (cmd->fd_infile == -1)
		{
			printf("minishell: %s: No such file or directory\n", cmd->infiles->filename);
			exit_tab(mini, 127);
		}
		else
		{
			if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
				exit_fd(cmd->outpipe, mini);
		}
		if (cmd->fd_outfile != -1)
		{
			if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
				exit_fd(cmd->fd_outfile, mini);
		}
		printf("sithomas la truite\n");
		if (!ft_exec_cmd(cmd, mini, head))
		{
			ft_close_fd(cmd, 0);
			exit_tab(mini, 127);
		}
		printf("jweber la nouille\n");
		close(cmd->outpipe);
	}
	close(cmd->outpipe);
	wait_children(pid_last, mini);
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
