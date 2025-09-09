/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:44:51 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 11:00:51 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
		&& (cmd->redir->next->type == INPUT))
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
