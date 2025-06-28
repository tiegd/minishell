/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_for_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:36:31 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/28 16:20:27 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Print le tableau de chaine de caractère passé en argument*/
void	print_tab_char(char **tab)
{
	int	i;
	
	i = 0;
	while (tab[i])
	{
		printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
}

/*permet de print une liste chainé de type t_token*/
void	ft_print_lst(t_token *lst)
{
	while (lst)
	{
		printf(RED"content = %s | type = %d\n"RESET, lst->content, lst->type);
		lst = lst->next;
	}
}

/*Print une liste chainé de type t_cmd*/
void	ft_print_cmd(t_cmd *lst)
{
	int i;
	while (lst)
	{
		i = 0;
		while (lst->args[i] != NULL)
		{
			printf(RED"cmd = %s | type = %d\n"RESET, lst->args[i], lst->type);
			i++;
		}
		lst = lst->next;
	}
}

void	ft_print_tab(char **path, int nb_path)
{
	int	i;
	
	i = 0;
	while (i != nb_path)
	{
		printf(YELLOW"path[%d] = %s\n"RESET, i,path[i]);
		i++;
	}
}
