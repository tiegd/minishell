/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:44:51 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 13:53:13 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>

void	close_fds(int infile, int outfile)
{
	if (infile > 0)
		close(infile);
	if (outfile > 1)
		close(outfile);
}

int	is_close(t_cmd *cmd)
{
	if (cmd->redir->next != NULL && cmd->fd_infile > 0
		&& (cmd->redir->next->type == INPUT
			|| cmd->redir->next->type == HERE_DOC))
	{
		if (close(cmd->fd_infile) == -1)
			return (0);
	}
	else if (cmd->redir->next != NULL && (cmd->redir->next->type == OUTPUT
			|| cmd->redir->next->type == APPEND) && cmd->fd_outfile > 1)
	{
		if (close(cmd->fd_outfile) == -1)
			return (0);
	}
	return (1);
}

int	close_all_here_doc(int *here_doc_list)
{
	int	i;

	i = 0;
	while (here_doc_list[i] != 0)
	{
		close(here_doc_list[i]);
		i++;
	}
	return (0);
}

void	close_both_fd(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
