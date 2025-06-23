/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/23 15:51:21 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count the number of '|' in the prompt.

// int	ft_count_pipe(t_token *lst)
// {
// 	t_token	*tmp;
// 	int		count;

// 	tmp = lst;
// 	count = 0;
// 	while (tmp->next)
// 	{
// 		if (tmp->type == PIPE)
// 			count++;
// 		tmp = tmp->next;
// 	}
// 	return (count);
// }

int	ft_count_pipe(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		count;

	tmp = cmd;
	count = 0;
	while (tmp->next)
	{
		count++;
		tmp = tmp->next;
	}
	printf("count = %d\n", count);
	return (count);
}

// Run the first command and redirect the output to the following command.

static void	first_pipe(t_cmd *cmd, char *envp[], t_token *lst)
{
	int	pid;
	int	pipefd[2];

	printf(YELLOW"in fisrt_pipe\n"RESET);
	if(pipe(pipefd) == -1)
		exit_tab(cmd, lst, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit_pid_error(pipefd, cmd, lst);
	printf(GREEN"pid = %d\n"RESET, pid);
	if (pid == 0)
	{
		printf("oui\n");
		printf(YELLOW"pipefd[0] = %d ; pipefd[1] = %d\n"RESET, pipefd[0], pipefd[1]);
		printf(CYAN"STDIN_FILENO = %d ; STDOUT_FILENO = %d\n"RESET, STDIN_FILENO, STDOUT_FILENO);
		if (cmd->infiles != NULL)
		{
			ft_open_infile(cmd);
			if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
				exit_fd(pipefd[1], cmd, lst);
		}
		printf("coucou\n");
		if (cmd->outfiles != NULL)
			ft_open_outfile(cmd);
		// printf(RED"dup2 = %d\n"RESET, dup2(pipefd[1], STDOUT_FILENO));
		printf("yo\n");
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			printf("ekip\n");
			exit_fd(cmd->fd_outfile, cmd, lst);
		}
		printf("lundi\n");
		if (!ft_exec_cmd(cmd, envp))
		{
			printf("mardi\n");
			ft_close_fd(cmd, pipefd);
			exit_tab(cmd, lst, 127);
		}
		printf("fin\n");
	}
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
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(pipefd[1], cmd, lst);
	}
}

// Run the the command and redirect the output to the terminal.

static void	last_pipe(t_cmd *cmd, char *envp[], t_token *lst)
{
	(void)cmd;
	(void)envp;
	(void)lst;
	return ;
}

// This function shall reproduce the behavior of '|' in bash.

void	pipex(t_cmd *cmd, char *envp[], int nb_pipe, t_token *lst)
{
	int	i;

	i = 0;
	printf(RED"nb_pipe = %d\n"RESET, nb_pipe);
	while (i < nb_pipe)
	{
		if (i == 0)
			first_pipe(cmd, envp, lst);
		else if (i == nb_pipe - 1)
			last_pipe(cmd, envp, lst);
		else
			middle_pipe(cmd, envp, lst);
		i++;
		cmd = cmd->next;
	}
}
