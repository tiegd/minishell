/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:53:27 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/12 17:10:06 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free all of the list (token).

void	ft_lstfree(t_token *lst)
{
	t_token	*tmp;

	if (lst)
	{
		while (lst)
		{
			tmp = lst;
    		lst = lst->next;
	    	free(tmp->content);
		    free(tmp);
		}
	}
}

// Free the redir list in cmd list (*infile and *outfile).

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir->next)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp);
	}
}

// Free double tab (**args)

void	free_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// Free cmd list.

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd->next)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_redir(tmp->fd_infile);
		free_redir(tmp->outfile);
		free_double_tab(tmp->args);
		free(tmp->pathname);
		free(tmp);
	}
}

// Free all of structs.

void	free_struct(t_cmd *cmd, t_token *lst)
{
	t_token	*tmp_lst;
	t_cmd	*tmp_cmd;

	free_token(lst);
	free_cmd(cmd);
}
