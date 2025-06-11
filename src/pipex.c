/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/11 14:20:41 by gaducurt         ###   ########.fr       */
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

int	ft_open_fd(t_fd *fd)
{
	fd->infile = open(fd->path_in, O_RDONLY);
	fd->outfile = open(fd->infile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd->infile < 0 || fd->outfile < 0)
		return (0);
	return (1);
}

int	ft_close_fd(t_fd *fd)
{
	if (close(fd->infile) == -1)
		return (0);
	if (close(fd->outfile) == -1)
		return (0);
	return (1);
}

int	ft_is_redir()
{
	
}

static void	first_pipe(t_cmd *cmd, char *envp[], t_fd *fd, int i)
{
	if (ft_is_redir(cmd->fd))
	return ;
}

static void	last_pipe(t_cmd *cmd, char *envp[], t_fd *fd, int i)
{
	return ;
}

void	exec_one_pipex(t_cmd *cmd, char *envp[], t_fd fd)
{
	first_pipe(cmd, envp, &fd, 0);
	last_pipe(cmd, envp, &fd, 1);
}

// void	exec_multi_pipex(t_cmd *cmd, char *envp[], t_fd fd)
// {
// 	first_pipe(cmd, envp, &fd, 0);
// 	last_pipe(cmd, envp, &fd, 1);
// }

void	pipex(t_token *lst, t_cmd *cmd, char **env, t_redir *redir)
{
	t_fd	fd;
	int		nb_pipe;
	int		i;

	nb_pipe = ft_count_pipe(lst);
	ft_fill_index(lst);
	while (i != nb_pipe)
	{
		if (!ft_open_fd(&fd))
			return ;
		if (nb_pipe == 1)
		{
			exec_one_pipex(cmd, env, fd);
		}
		if (nb_pipe > 1)
		{
			exec_multi_pipex(cmd, env, fd);
		}
		if (!ft_close_fd(&fd));
			return ;
		cmd = cmd->next;
		i++;
	}
}
