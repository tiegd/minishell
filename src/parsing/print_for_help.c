/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_for_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:36:31 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/19 11:50:55 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Print le tableau de chaine de caractère passé en argument*/
void	print_tab_char(char **tab)
{
	int	i;
	
	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
}

/*permet de print une liste chainé de type t_token*/
void	ft_print_lst(t_token *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf(RED"content = %s | type = %d\n"RESET, lst->content, lst->type);
		lst = lst->next;
	}
}

/*permet de print une liste chainé de type t_gmalloc*/
void	ft_print_memory(t_gmalloc *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		printf(RED"memory address[%d] = %p\n", i, lst->memory);
		if (lst->next == NULL)
			return ;
		lst = lst->next;
		i++;
	}
}

/*Print une liste chainé de type t_cmd*/
void	ft_print_cmd(t_cmd *lst)
{
	int i;
	int j = 0;
	while (lst)
	{
		i = 0;
		while (lst->args[i] != NULL)
		{
			printf(RED"cmd[%d] = %s | type = %d\n"RESET, j, lst->args[i], lst->type);
			printf("infiles redir = %s\n", lst->infiles->filename);
			printf("outfiles redir = %s\n", lst->outfiles->filename);
			i++;
		}
		lst = lst->next;
		j++;
	}
}

void	ft_print_tab(char **path, int nb_path)
{
	int	i;
	
	i = 0;
	if (!path && !(*path))
		return ;
	while (i != nb_path)
	{
		printf(YELLOW"path[%d] = %s\n"RESET, i,path[i]);
		i++;
	}
}

void	print_tab_int(int *tab)
{
	int i = 0;

	while (tab[i])
	{
		printf("%d\n", tab[i]);
		i++;
	}
}

void	ft_print_redir(t_redir *lst)
{
	int i;

	while (lst)
	{
		i = 0;
		printf(RED"redir = %s | type = %d\n"RESET, lst->filename, lst->type);
		i++;
		lst = lst->next;
	}
}
