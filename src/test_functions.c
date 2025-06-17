/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:17:56 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/16 15:19:03 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Test function.

void	ft_print_tab(char **path, int nb_path)
{
	int	i;
	
	i = 0;
	while (i != nb_path)
	{
		printf(YELLOW"path = %s\n"RESET, path[i]);
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
