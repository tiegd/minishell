/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/15 12:00:25 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Run the first command and redirect the output to the following command.

static void	first_pipe(t_cmd *cmd, char **env, t_gmalloc **head)
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
		if (cmd->infiles != NULL || cmd->outfiles != NULL)
			ft_fd_to_pipe(cmd);
		if (cmd->outfiles == NULL)
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit_fd(pipefd[1], cmd);
		close(pipefd[0]);
		close(pipefd[1]);
		if (!ft_exec_cmd(cmd, env, head))
		{
			ft_close_fd(cmd, pipefd);
			exit_tab(cmd, 127);
		}
	}
	close(pipefd[1]);
	cmd->outpipe = pipefd[0];
}

// Run a middle command and redirect the output to the following command.

static void	middle_pipe(t_cmd *cmd, char **env, t_gmalloc **head)
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
		if (cmd->infiles != NULL || cmd->outfiles != NULL)
			ft_fd_to_pipe(cmd);
		if (cmd->infiles == NULL)
			if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
				exit_fd(cmd->outpipe, cmd);
		if (cmd->outfiles == NULL)
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit_fd(pipefd[1], cmd);
		close(pipefd[0]);
		close(pipefd[1]);
		if (!ft_exec_cmd(cmd, env, head))
		{
			ft_close_fd(cmd, pipefd);
			exit_tab(cmd, 127);
		}
	}
	close(pipefd[1]);
	cmd->outpipe = pipefd[0];
}

// Run the the command and redirect the output to the terminal.

static void	last_pipe(t_cmd *cmd, char **env, t_gmalloc **head)
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
		if (!ft_exec_cmd(cmd, env, head))
			exit_tab(cmd, 127);
		exit_tab(cmd, 1);
	}
	close(cmd->outpipe);
	wait_children(pid_last, cmd);
}

// This function shall reproduce the behavior of '|' in bash.

void	pipex(t_cmd *cmd, char **env, int nb_pipe, t_gmalloc **head)
{
	int	i;

	i = 0;
	// printf(RED"nb_pipe = %d\n"RESET, nb_pipe);
	while (i <= nb_pipe)
	{
		if (i == 0)
			first_pipe(cmd, env, head);
		else if (i == nb_pipe)
			last_pipe(cmd, env, head);
		else
			middle_pipe(cmd, env, head);
		if (i < nb_pipe)
			cmd->next->outpipe = cmd->outpipe;
		i++;
		cmd = cmd->next;
	}
}
