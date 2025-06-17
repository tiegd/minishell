/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:17:56 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/17 15:25:53 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Test function.

void	ft_print_tab(char **path, int nb_path)
{
	int	i;
	
	i = 0;
	(void)nb_path;
	// while (i != nb_path)
	while (path[i][0] != '\0')
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

// int	test_count_tab(char **args)
// {
// 	int	i;

// 	i = 0;
// 	while (args[i][0] != NULL)
	
// }


void	ft_print_cmd(t_cmd *lst)
{
	int i;
	while (lst)
	{
		i = 0;
		while (lst->args[i] != NULL)
		{
			printf(GREEN"cmd = %s type = %d\n"RESET, lst->args[i], lst->type);
			i++;
		}
		lst = lst->next;
	}
}
