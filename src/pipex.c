/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/12 17:18:13 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count the number of '|' in the prompt.

int	ft_count_pipe(t_token *lst)
{
	t_token	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while (tmp->next)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
// Run the first command and redirect the output to the following command.

static void	first_pipe(t_cmd *cmd, char *envp[], int i, t_token *lst)
{
	int	pid;
	int	pipefd[2];

	if(pipe(pipefd) == -1)
		exit_tab(cmd, lst, EXIT_FAILURE);
	pid = fork();
	// if (pid == -1)
	// 	exit_pid_error();
	if (pid == 0)
	{
		ft_open_fd(cmd);
		if (dup2(cmd->fd_infile, STDIN_FILENO) == -1)
			exit_fd(pipefd[1], cmd, lst);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit_fd(cmd->fd_outfile, cmd, lst);
		if (cmd->pathname != NULL)
			execve(cmd->pathname, cmd->args, envp);
		exit_tab(cmd, lst, EXIT_FAILURE);
		ft_exec_builtin(cmd);
	}
	ft_close_fd(cmd, pipefd);
}

// Run the the command and redirect the output to the terminal.

static void	last_pipe(t_cmd *cmd, char *envp[], int i, t_token *lst)
{
	return ;
}

// Run the a middle command and redirect the output to the following command.

static void	middle_pipe(t_cmd *cmd, char *envp[], int i, t_token *lst)
{
	return ;
}

// Run two commands if we have a single pipe.

void	exec_one_pipex(t_cmd *cmd, char *envp[], int nb_pipe, t_token *lst)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		if (i == 0)
			first_pipe(cmd, envp, i, lst);
		else if (i == nb_pipe - 1)
			last_pipe(cmd, envp, i, lst);
		else
			middle_pipe(cmd, envp, i, lst);
		cmd = cmd->next;
	}
}

// // Run several commands if we have more than one pipe.

// void	exec_multi_pipex(t_cmd *cmd, char *envp[], int nb_pipe)
// {
// 	first_pipe(cmd, envp, &fd, 0);
// 	last_pipe(cmd, envp, &fd, 1);
// }

// This function shall reproduce the behavior of '|' in bash.

void	pipex(t_token *lst, t_cmd *cmd, char **env)
{
	int		nb_pipe;

	nb_pipe = ft_count_pipe(lst);
	ft_fill_index(lst);
	if (nb_pipe == 1)
		exec_one_pipex(cmd, env, nb_pipe, lst);
	if (nb_pipe > 1)
		exec_multi_pipex(cmd, env, nb_pipe, lst);
}
