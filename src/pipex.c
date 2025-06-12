/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/12 16:27:55 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
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

// // Fill the index of each token in lst. Index is 1 afeter a pipe.

// void	ft_fill_index(t_token *lst)
// {
// 	t_token	*tmp;
// 	int		index;
	
// 	tmp = lst;
// 	index = 1;
// 	while (tmp->next)
// 	{
// 		if (tmp->type == PIPE)
// 				index = 0;
// 		tmp->index = index;
// 		index++;
// 		tmp = tmp->next;
// 	}
// }

void	ft_init_fd(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		if (tmp->type == INPUT || tmp->type == OUTPUT || tmp->type == APPEND)
		{
			tmp = tmp->next;
			tmp->type = FD;
		}
		tmp = tmp->next;
	}
}

int	ft_open_fd(t_cmd *cmd)
{
	while (cmd->infile->next)
	{
		cmd->fd_infile = open(cmd->infile->filename, O_RDONLY);
		if (cmd->fd_infile < 0)
			return (0);
		if (cmd->infile->next != NULL)
		{
			if (close(cmd->fd_infile) == -1)
				return (0);
		}
		cmd->infile = cmd->infile->next;
	}
	while (cmd->outfile->next)
	{
		cmd->fd_outfile = open(cmd->outfile->filename, O_RDONLY | O_CREAT | O_TRUNC, 0666);
		if (cmd->fd_outfile < 0)
			return (0);
		if (cmd->outfile->next != NULL)
		{
			if (close(cmd->fd_outfile) == -1)
				return (0);
		}
		cmd->outfile = cmd->outfile->next;
	}
	return (1);
}

int	ft_close_fd(t_cmd *cmd, int *pipefd)
{
	if (cmd->fd_infile >= 0)
	{
		if (close(cmd->fd_infile) == -1)
			return (0);
	}
	if (cmd->fd_outfile >= 0)
	{
		if (close(cmd->fd_outfile) == -1)
			return (0);
	}
	if (pipefd[0] >= 0 )
	{
		if (close(pipefd) == -1)
			return (0);
	}
	if (pipefd[1] >= 0)
	{
		if (close(pipefd[1]) == -1)
			return (0);
	}
	return (1);
}

void	free_struct()

void	exit_pid_error(int *pipefd, t_cmd *cmd)
{
	
}

void	exit_tab(t_cmd *cmd, t_token *lst, int code)
{
	free_struct(lst);
	free_struct(cmd);
	free_struct(cmd);
	exit(code);
}

void	exit_fd(int fd, t_cmd *cmd, t_token *lst)
{
	if (fd > 0)
		close(fd);
	// free_struct(lst);
	// free_struct(cmd->infile);
	// free_struct(cmd->outfile);
	// free_struct_cmd(cmd);
	perror("No such file or directory");
	exit(EXIT_FAILURE);
}

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

static void	last_pipe(t_cmd *cmd, char *envp[], int i, t_token *lst)
{
	return ;
}

static void	middle_pipe(t_cmd *cmd, char *envp[], int i, t_token *lst)
{
	return ;
}

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

// void	exec_multi_pipex(t_cmd *cmd, char *envp[], int nb_pipe)
// {
// 	first_pipe(cmd, envp, &fd, 0);
// 	last_pipe(cmd, envp, &fd, 1);
// }

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
