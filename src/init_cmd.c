/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:22:52 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/11 10:14:49 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*remplir chaques paramètre d'un nouvelle commande*/
t_cmd *new_cmd(t_token *token)
{
	t_cmd *new;
	
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	while (token->next != NULL || token->type != PIPE)
	{
		if (token->type == INPUT)
		{
			new->infile = open(token->next->content, O_RDONLY);
			token = token->next->next;
		}
		else if (token->type == OUTPUT)
		{
			new->outfile = open(token->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			token = token->next->next;
		}
		else if (token->type == APPEND)
		{
			new->outfile = open(token->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			token = token->next->next;
		}
		else if
	}
}

/*initialiser chaque commande en les séparants par pipe*/
t_cmd	*ft_init_cmd(t_token *token)
{
	t_cmd	*head;
	t_cmd	*cmd;

	head = NULL;
	while (token->next != NULL || token->type != PIPE)
	{
		if (!cmd)
			cmd = malloc(sizeof(t_cmd));
		else
			cmd_add_back(&head, new_cmd);
		if (token->type == OUTPUT)
		{
			token->next->content 
		}
	}
	if (token->type == PIPE)
	{
		token = token->next;
		cmd = cmd->next;
	}
}