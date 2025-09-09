/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:53:27 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/09 08:25:41 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free all of the list (token).

void	free_token(t_token *lst, t_gmalloc **head)
{
	t_token	*tmp;
	int i = 1;

	if (lst)
	{
		while (lst)
		{
			// printf("token free = %d\n", i);
			tmp = lst;
			lst = lst->next;
			gfree(tmp->content, head);
			gfree(tmp, head);
		}
	}
}

// Free the redir list in cmd list (*infile and *outfile).

void	free_redir(t_redir *redir, t_gmalloc **head)
{
	t_redir	*tmp;

	if (redir)
	{
		while (redir)
		{
			tmp = redir;
			redir = redir->next;
			gfree(tmp->filename, head);
			gfree(tmp, head);
		}
	}
}

// Free double tab (**args)

char	**free_double_tab(char **tab, int nb_agrs, t_gmalloc **head)
{
	int	i;

	i = 0;
	while (i < nb_agrs)
	{
		gfree(tab[i], head);
		i++;
	}
	gfree(tab, head);
	return (NULL);
}

// Free cmd list.

void	free_cmd(t_cmd *cmd, t_gmalloc **head)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
			free_prompt(tmp->args, head);
		if (tmp->pathname)
			gfree(tmp->pathname, head);
		gfree(tmp, head);
	}
}

void	free_one_cmd(t_cmd *cmd, t_gmalloc **head)
{
	if (cmd)
	{
		if (cmd->args)
			free_prompt(cmd->args, head);
		if (cmd->pathname)
			gfree(cmd->pathname, head);
		gfree(cmd, head);
	}
}
