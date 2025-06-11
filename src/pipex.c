/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/11 11:24:12 by gaducurt         ###   ########.fr       */
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

void	ft_open_fd(t_token *lst, t_fd *fd)
{
	t_token	*tmp;
	int		infile;
	int		outfile;
	
	tmp = lst;
	while (tmp->type != '|')
	{
		if (tmp->type == FD)
	}
}

static void	first_pipe(t_cmd *cmd, char *envp[], t_fd *fd, int i)
{
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

void	exec_multi_pipex(t_cmd *cmd, char *envp[], t_fd fd)
{
	first_pipe(cmd, envp, &fd, 0);
	last_pipe(cmd, envp, &fd, 1);
}

void	pipex(t_token *lst, t_cmd *cmd, char **env)
{
	t_fd	fd;
	int		nb_pipe;
	int		i;

	nb_pipe = ft_count_pipe(lst);
	ft_fill_index(lst);
	ft_open_fd(lst, &fd);
	while (i != nb_pipe)
	{
		if (nb_pipe == 1)
		{
			exec_one_pipex(cmd, env, fd);
		}
		if (nb_pipe > 1)
		{
			exec_multi_pipex(cmd, env, fd);
		}
		i++;
	}
}
