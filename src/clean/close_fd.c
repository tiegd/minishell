/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:44:51 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/10 18:31:20 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>

void	close_fds(int infile, int outfile)
{
	if (infile > 0)
	{
		if (close(infile) == -1)
		{
			rl_clear_history();
			exit(1);
		}
	}
	if (outfile > 1)
	{
		if (close(outfile) == -1)
		{
			rl_clear_history();
			exit(1);
		}
	}
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
