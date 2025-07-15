/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:53:27 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/15 11:29:23 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free all of the list (token).

void	ft_lstfree(t_token *lst, t_gmalloc **head)
{
	t_token	*tmp;

	if (lst)
	{
		while (lst)
		{
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

	while (redir->next)
	{
		tmp = redir;
		redir = redir->next;
		gfree(tmp, head);
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

	while (cmd->next)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_redir(tmp->infiles, head);
		free_redir(tmp->outfiles, head);
		free_double_tab(tmp->args, tmp->nb_agrs, head);
		gfree(tmp->pathname, head);
		gfree(tmp, head);
	}
}
