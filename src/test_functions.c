/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:17:56 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/18 11:11:05 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Test function.

void	ft_print_tab(char **tab)
{
	int	i;
	
	i = 0;
	while (tab[i] != NULL)
	{
		printf(GREEN"tab[%d] = %s\n"RESET, i, tab[i]);
		i++;
	}
}

// Just for test the list. This function will be deleted.

void	ft_print_lst(t_token *lst)
{
	while (lst)
	{
		printf(RED"content = %s | type = %d\n"RESET, lst->content, lst->type);
		// printf("type = %d\n")
		lst = lst->next;
	}
}

void	ft_print_cmd(t_cmd *lst)
{
	t_cmd	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_print_tab(tmp->args);
		tmp = tmp->next;
	}
}
