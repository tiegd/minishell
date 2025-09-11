/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:22:52 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 13:44:40 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "gblib.h"
#include "clean.h"
#include "parsing.h"

/*Fill the redirections.*/

static t_redir	*add_redir(t_redir *list, t_token *token, t_gmalloc **head)
{
	t_redir	*new;
	t_redir	*temp;

	new = gb_malloc(sizeof(t_redir), head);
	new->filename = gb_strdup(token->next->content, head);
	new->type = token->type;
	new->next = NULL;
	if (!list)
		return (new);
	temp = list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return (list);
}

/*Add the new node at the linked list.*/

static void	cmd_add_back(t_cmd **head, t_cmd *new_node)
{
	t_cmd	*temp;

	if (!new_node)
		return ;
	temp = *head;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

/*Creat a new cmd node at the linked list.*/

static t_cmd	*new_cmd(t_gmalloc **gmalloc)
{
	t_cmd	*new;

	new = gb_malloc(sizeof(t_cmd), gmalloc);
	new->fd_infile = 0;
	new->fd_outfile = 1;
	new->outpipe = -1;
	new->fd_here_doc = 0;
	new->pathname = NULL;
	new->paths = NULL;
	new->redir = NULL;
	new->next = NULL;
	return (new);
}

/*Init each command by separting the infiles from the arguments.*/

static void	handle_cmd_args(t_cmd *cmd, t_token **token, t_gmalloc **head)
{
	int	i;

	i = 0;
	while (*token != NULL && (*token)->type != PIPE)
	{
		if ((*token)->type == OUTPUT || (*token)->type == APPEND
			|| (*token)->type == HERE_DOC || (*token)->type == INPUT)
		{
			cmd->redir = add_redir(cmd->redir, *token, head);
			*token = (*token)->next->next;
		}
		else
		{
			if ((*token)->content[0] != '\0')
				cmd->args[i] = gb_strdup((*token)->content, head);
			else
			{
				cmd->args[i] = gb_malloc(sizeof(char), head);
				cmd->args[i][0] = '\0';
			}
			i++;
			*token = (*token)->next;
		}
	}
	cmd->args[i] = NULL;
}

/*Init each command by spliting at each pipe*/

t_cmd	*init_cmd(t_token **token, t_gmalloc **gmalloc)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	*token_head;
	int		n_args;

	head = NULL;
	n_args = count_args(*token);
	token_head = *token;
	while (*token)
	{
		cmd = new_cmd(gmalloc);
		cmd->args = gb_malloc((n_args + 1) * sizeof(char *), gmalloc);
		handle_cmd_args(cmd, token, gmalloc);
		cmd_add_back(&head, cmd);
		if (*token)
			(*token) = (*token)->next;
	}
	free_token(token_head, gmalloc);
	return (head);
}
