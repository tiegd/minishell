/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/11 17:26:15 by gaducurt         ###   ########.fr       */
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

int	ft_close_fd(t_cmd *cmd)
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
	return (1);
}

static void	first_pipe(t_cmd *cmd, char *envp[], int i)
{
	if (cmd->args[0])
	return ;
}

static void	last_pipe(t_cmd *cmd, char *envp[], int i)
{
	return ;
}

void	exec_one_pipex(t_cmd *cmd, char *envp[])
{
	first_pipe(cmd, envp, 0);
	last_pipe(cmd, envp, 1);
}

// void	exec_multi_pipex(t_cmd *cmd, char *envp[])
// {
// 	first_pipe(cmd, envp, &fd, 0);
// 	last_pipe(cmd, envp, &fd, 1);
// }

void	pipex(t_token *lst, t_cmd *cmd, char **env)
{
	int		nb_pipe;
	int		i;

	nb_pipe = ft_count_pipe(lst);
	ft_fill_index(lst);
	while (i != nb_pipe)
	{
		ft_open_fd(cmd);
		if (nb_pipe == 1)
			exec_one_pipex(cmd, env);
		if (nb_pipe > 1)
			exec_multi_pipex(cmd, env);
		ft_close_fd(cmd);
		cmd = cmd->next;
		i++;
	}
}
