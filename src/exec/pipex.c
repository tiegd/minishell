/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/04 09:47:32 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Run the first command and redirect the output to the following command.

static void	first_pipe(t_cmd *cmd, char **env)
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
		printf("Robin la fièvre\n");
		if (cmd->fd_infile)
		{
			printf("pdp la quiche\n");
			if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
				exit_fd(cmd->fd_infile, cmd);
		}
		if (cmd->fd_outfile)
		{
			printf("Jules le bbq\n");
			if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
				exit_fd(cmd->fd_outfile, cmd);
		}
		else
		{
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			{
				printf("le blé ou le mouton ?\n");
				exit_fd(pipefd[1], cmd);
			}
		}
		close(pipefd[0]);
		close(pipefd[1]);
		// printf("Jocelyn la piche\n");
		if (!ft_exec_cmd(cmd, env))
		{
			ft_close_fd(cmd, pipefd);
			exit_tab(cmd, 127);
		}
	}
	close(pipefd[1]);
	cmd->outpipe = pipefd[0];
}

// Run a middle command and redirect the output to the following command.

static void	middle_pipe(t_cmd *cmd, char **env)
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
		// if (cmd->infiles != NULL || cmd->outfiles != NULL)
		// 	ft_fd_to_pipe(cmd);
		ft_open_fd(cmd);
		if (cmd->fd_infile)
		{
			printf("simon la mouche\n");
			if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
				exit_fd(cmd->fd_infile, cmd);
		}
		if (cmd->fd_outfile)
		{
			printf("Yazid le niglo\n");
			if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
				exit_fd(cmd->fd_outfile, cmd);
		}
		if (cmd->infiles == NULL)
			if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
				exit_fd(cmd->outpipe, cmd);
		if (cmd->outfiles == NULL)
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit_fd(pipefd[1], cmd);
		close(pipefd[0]);
		close(pipefd[1]);
		if (!ft_exec_cmd(cmd, env))
		{
			ft_close_fd(cmd, pipefd);
			exit_tab(cmd, 127);
		}
	}
	close(pipefd[1]);
	cmd->outpipe = pipefd[0];
}

// Run the the command and redirect the output to the terminal.

static void	last_pipe(t_cmd *cmd, char **env)
{
	int	pid_last;

	pid_last = fork();
	if (pid_last == -1)
		exit_tab(cmd, EXIT_FAILURE);
	if (pid_last == 0)
	{
		if (cmd->infiles != NULL || cmd->outfiles != NULL)
			ft_fd_to_pipe(cmd);
		if (cmd->infiles == NULL)
			if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
				exit_fd(cmd->outpipe, cmd);
		close(cmd->outpipe);
		if (!ft_exec_cmd(cmd, env))
			exit_tab(cmd, 127);
		exit_tab(cmd, 1);
	}
	close(cmd->outpipe);
	wait_children(pid_last, cmd);
}

// This function shall reproduce the behavior of '|' in bash.

void	pipex(t_cmd *cmd, char **env, int nb_pipe)
{
	int	i;

	i = 0;
	// printf(RED"nb_pipe = %d\n"RESET, nb_pipe);
	while (i <= nb_pipe)
	{
		if (i == 0)
			first_pipe(cmd, env);
		else if (i == nb_pipe)
			last_pipe(cmd, env);
		else
			middle_pipe(cmd, env);
		if (i < nb_pipe)
			cmd->next->outpipe = cmd->outpipe;
		i++;
		cmd = cmd->next;
	}
}
