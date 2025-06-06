/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/06 14:48:13 by gaducurt         ###   ########.fr       */
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
		if (ft_strlen(tmp->content) == 1 && tmp->content[0] == '|')
				count++;
		tmp = tmp->next;
	}
	return (count);
}

// Fill the index of each token in lst. Index is 1 afeter a pipe.

void	ft_fill_lst(t_token *lst)
{
	t_token	*tmp;
	int		index;
	
	tmp = lst;
	index = 1;
	while (tmp->next)
	{
		if (ft_strlen(tmp->content) == 1 && tmp->content[0] == '|')
				index = 0;
		tmp->index = index;
		index++;
		tmp = tmp->next;
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

void	exec_pipex(t_cmd *cmd, char *envp[], t_fd fd)
{
	first_pipe(cmd, envp, &fd, 0);
	last_pipe(cmd, envp, &fd, 1);
	
}

void	pipex(t_token *lst, t_cmd *cmd, char **env)
{
	int	nb_pipe;

	nb_pipe = ft_count_pipe(lst);
	ft_fill_index(lst);
	if (nb_pipe == 1)
	{
		
	}
	if (nb_pipe > 1)
	{
		
	}
}
