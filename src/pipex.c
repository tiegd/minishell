/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/30 10:42:19 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Run the first command and redirect the output to the following command.

static void	first_pipe(t_cmd *cmd, char *envp[], t_token *lst)
{
	int	pid;
	int	pipefd[2];

	if(pipe(pipefd) == -1)
		exit_tab(cmd, lst, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit_pid_error(pipefd, cmd, lst);
	if (pid == 0)
	{
		if (cmd->infiles != NULL || cmd->outfiles != NULL)
			ft_fd_to_pipe(cmd, lst);
		if (cmd->outfiles == NULL)
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit_fd(pipefd[1], cmd, lst);
		close(pipefd[0]);
		close(pipefd[1]);
		if (!ft_exec_cmd(cmd, envp))
		{
			ft_close_fd(cmd, pipefd);
			exit_tab(cmd, lst, 127);
		}
	}
	close(pipefd[1]);
	cmd->outpipe = pipefd[0];
}

// Run a middle command and redirect the output to the following command.

static void	middle_pipe(t_cmd *cmd, char *envp[], t_token *lst)
{
	int	pid;
	int	pipefd[2];

	(void)envp;
	if (pipe(pipefd) == -1)
		exit_tab(cmd, lst, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit_pid_error(pipefd, cmd, lst);
	if (pid == 0)
	{
		if (cmd->infiles != NULL || cmd->outfiles != NULL)
			ft_fd_to_pipe(cmd, lst);
		if (cmd->infiles == NULL)
			if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
				exit_fd(cmd->outpipe, cmd, lst);
		if (cmd->outfiles == NULL)
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				exit_fd(pipefd[1], cmd, lst);
		close(pipefd[0]);
		close(pipefd[1]);
		if (!ft_exec_cmd(cmd, envp))
		{
			ft_close_fd(cmd, pipefd);
			exit_tab(cmd, lst, 127);
		}
	}
	close(pipefd[1]);
	cmd->outpipe = pipefd[0];
}

// Run the the command and redirect the output to the terminal.

static void	last_pipe(t_cmd *cmd, char *envp[], t_token *lst)
{
	int	pid_last;

	pid_last = fork();
	if (pid_last == -1)
		exit_tab(cmd, lst, EXIT_FAILURE);
	if (pid_last == 0)
	{
		if (cmd->infiles != NULL || cmd->outfiles != NULL)
			ft_fd_to_pipe(cmd, lst);
		if (cmd->infiles == NULL)
			if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
				exit_fd(cmd->outpipe, cmd, lst);
		close(cmd->outpipe);
		if (!ft_exec_cmd(cmd, envp))
			exit_tab(cmd, lst, 127);
		exit_tab(cmd, lst, 1);
	}
	close(cmd->outpipe);
	wait_children(pid_last, cmd);
}

// This function shall reproduce the behavior of '|' in bash.

void	pipex(t_cmd *cmd, char *envp[], int nb_pipe, t_token *lst)
{
	int	i;

	i = 0;
	// printf(RED"nb_pipe = %d\n"RESET, nb_pipe);
	while (i <= nb_pipe)
	{
		if (i == 0)
			first_pipe(cmd, envp, lst);
		else if (i == nb_pipe)
			last_pipe(cmd, envp, lst);
		else
			middle_pipe(cmd, envp, lst);
		if (i < nb_pipe)
			cmd->next->outpipe = cmd->outpipe;
		i++;
		cmd = cmd->next;
	}
}
