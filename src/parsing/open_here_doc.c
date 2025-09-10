/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:27:27 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/10 18:25:14 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdio.h"

int	open_for_each_redir(t_redir **head, t_cmd *cmd, t_mini *mini)
{
	t_redir	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->type == HERE_DOC)
		{
			if (cmd->fd_here_doc > 1)
				close(cmd->fd_here_doc);
			cmd->fd_here_doc = create_here_doc(mini, temp->filename,
					&mini->gmalloc);
			if (cmd->fd_here_doc <= 0)
			{
				if (cmd->fd_here_doc == -1)
				{
					mini->exit_status = 1;
					ft_putstr_fd("error occured during \
the creation of here document(s)\n", 2);
				}
				return (-1);
			}
		}
		temp = temp->next;
	}
	return (0);
}

int	open_for_each_cmd(t_cmd **head, t_mini *mini)
{
	t_cmd	*temp;
	int		i;

	i = 0;
	temp = *head;
	while (temp != NULL)
	{
		if (open_for_each_redir(&temp->redir, temp, mini) != 0)
			return (-1);
		mini->here_doc_list[i] = temp->fd_here_doc;
		temp = temp->next;
		i++;
	}
	mini->here_doc_list[i] = 0;
	return (0);
}
