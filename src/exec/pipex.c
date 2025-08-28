/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/28 10:08:05 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_first_pipe(t_mini *mini, t_cmd *cmd, int *pipefd)
{
	if (cmd->fd_infile != -1 && cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(cmd->fd_infile, mini);
	}
	else if (cmd->fd_infile == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd->infiles->filename);
		exit_tab(mini, 1);
	}
	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 1)
	{
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
			exit_fd(cmd->fd_outfile, mini);
	}
	else if (cmd->fd_outfile == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd->outfiles->filename);
		exit_tab(mini, 1);
	}
	else
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit_fd(pipefd[1], mini);
	}
}

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
		if (!ft_open_fd(cmd, mini))
			exit_tab(mini, 1);
		redir_first_pipe(mini, cmd, pipefd);
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

static void	redir_middle_pipe(t_mini *mini, t_cmd *cmd, int *pipefd)
{
	if (cmd->fd_infile != -1 && cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(cmd->fd_infile, mini);
	}
	else if (cmd->fd_infile == -1)
		print_error(mini, cmd->infiles->filename, "Permission denied", 1);
	// {
	// 	printf("minishell: %s: Permission denied\n", cmd->infiles->filename);
	// 	exit_tab(mini, 1);
	// }
	else
		if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
			exit_fd(cmd->outpipe, mini);
	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 1)
	{
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
			exit_fd(cmd->fd_outfile, mini);
	}
	if (cmd->fd_outfile == -1)
		print_error(mini, cmd->outfiles->filename, "Permission denied", 1);
	// {
	// 	printf("minishell: %s: Permission denied\n", cmd->outfiles->filename);
	// 	exit_tab(mini, 1);
	// }
	else
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit_fd(pipefd[1], mini);
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
		if (!ft_open_fd(cmd, mini))
			exit_tab(mini, 1);
		redir_middle_pipe(mini, cmd, pipefd);
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

static void	redir_last_pipe(t_mini *mini, t_cmd *cmd)
{
	if (cmd->fd_infile != -1 && cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(cmd->fd_infile, mini);
	}
	else if (cmd->fd_infile == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd->infiles->filename);
		exit_tab(mini, 1);
	}
	else
	{
		if (dup2(cmd->outpipe, STDIN_FILENO) == -1)
			exit_fd(cmd->outpipe, mini);
	}
	if (cmd->fd_outfile != -1 && cmd->fd_outfile != 1)
	{
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) == -1)
			exit_fd(cmd->fd_outfile, mini);
	}
	else if (cmd->fd_outfile == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd->outfiles->filename);
		exit_tab(mini, 1);
	}
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
		if (!ft_open_fd(cmd, mini))
			exit_tab(mini, 1);
		redir_last_pipe(mini, cmd);
		if (!ft_exec_cmd(cmd, mini, head))
		{
			ft_close_fd(cmd, 0);
			exit_tab(mini, 127);
		}
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
	mini->dup_std[0] = dup(STDIN_FILENO);
	mini->dup_std[1] = dup(STDOUT_FILENO);
	while (cmd)
	{
		extract_path(cmd, mini, head);
		ft_is_bin(cmd, mini);
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
	if (sig_flag != 0)
		write(STDOUT_FILENO, "\n", 1);
}
