/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:22:52 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/11 18:11:11 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*remplir les redirections*/
t_redir		*add_redir(t_redir *list, t_token *token)
{
	t_redir		*new;
	
	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->filename = ft_strdup(token->next->content);
	if (!new->filename)
		return (NULL);
	new->type = token->type;
	new->next = NULL;
	if (!list)
		return	(new);
	t_redir *temp;

	temp = list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return (list);
}

/*ajoute le nouveau noeud à la liste chainée*/
void	cmd_add_back(t_cmd **head, t_cmd *new_node)
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

/*creer une nouveau noeud commande pour la list chainé*/
t_cmd *new_cmd(void)
{
	int		i;
	t_cmd	*new;

	i = 0;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	// new->args = NULL;
	new->outfiles = NULL;
	new->infiles = NULL;
	return (new);
}

// int		count_args(char **args)
// {
// 	int count;

// 	count = 0;
// 	if (!args)
// 		return (count);
// 	while (args[count])
// 	{
// 		count++;
// 	}
// 	return (count);
// }

// char	**add_alloc(char **old)
// {
// 	char	**new;
// 	int		len_tab;
	
// 	if(!old)
// 	{
// 		new = malloc(sizeof(char *));
// 		if (!new)
// 		{
// 			// perror("malloc error");
// 			return (NULL);
// 		}
// 		return (new);
// 	}
// 	len_tab = count_args(old);
// 	new = malloc(sizeof(char *) * len_tab);
// 	if ()
	
	
	
// }

// 	if(!old)
// 	{
// 		new = malloc(sizeof(char *));
// 		if (!new)
// 			return (malloc(sizeof))
// 	}
// }

/*compte le nombre d'args qu'il y a dans le prompte rentré*/
int		count_args(t_token	*token)
{
	int count;

	count = 0;
	while (token)
	{
		if (token->type == APPEND || token->type == HERE_DOC 
			|| token->type == INPUT || token->type == OUTPUT)
			token = token->next->next;
		else if (token && token->type == PIPE)
			token = token->next;
		else if (token)
		{
			count++;
			token = token->next;
		}
		else
			break;
	}
	return (count);
}


/*initialiser chaque commande en les séparants par pipe*/
t_cmd	*ft_init_cmd(t_token *token)
{
	t_cmd	*head;
	t_cmd	*cmd;
	int		i;
	int		n_args;

	head = NULL;
	n_args = count_args(token);
	while (token && token->next != NULL)
	{
		i = 0;
		cmd = new_cmd();
		if (!cmd) //secu
		{
			//perror(malloc);
			//free_list
			return (NULL);
		}
		cmd->args = ft_calloc(n_args + 1, sizeof(char *));
		if (!cmd->args) //secu
		{
			//perror(malloc);
			//free_list
			return (NULL);
		}
		while (token && token->next != NULL && token->type != PIPE)
		{
			printf("error\n");
			if (token->type == OUTPUT || token->type == APPEND)
			{
				cmd->outfiles = add_redir(cmd->outfiles, token);
				token = token->next->next;
			}
			else if (token->type == HERE_DOC || token->type == INPUT)
			{
				cmd->infiles = add_redir(cmd->infiles, token);
				token = token->next->next;
			}
			else
			{
				cmd->args[i] = ft_strdup(token->content);
				i++;
				token = token->next;
			}
		}
		cmd->args[i] = NULL;
		cmd_add_back(&head, cmd);
		if (token)
			token = token->next;
		else 
			break;
	}
	return (head);
}


// /*remplir chaques paramètre d'un nouvelle commande*/
// t_cmd *new_cmd(t_cmd *cmd, t_token *token)
// {
// 	int		i;
// 	t_cmd	*new;
// 	t_cmd	*temp;

// 	i = 0;
// 	new = malloc(sizeof(t_cmd));
// 	if (!new)
// 		return (NULL);
// 	new->outfiles = NULL;
// 	new->infiles = NULL;

// 	while (token->next != NULL || token->type != PIPE)
// 	{
// 		if (token->type == OUTPUT || token->type == APPEND)
// 		{
// 			new->outfiles = add_redir(new->outfiles, token);
// 			token = token->next->next;
// 		}
// 		else if (token->type == HERE_DOC || token->type == INPUT)
// 		{
// 			new->infiles = add_redir(new->infiles, token);
// 			token = token->next->next;
// 		}
// 		else
// 		{
// 			new->args[i] = ft_strdup(token->content);
// 			i++;
// 			token = token->next;
// 		}
// 	}
// 	if (!cmd)
// 		return (new);
// 	temp = cmd;
// 	while(temp->next != NULL)
// 		temp = temp->next;
// 	temp->next = new;
// 	return (temp);
// }