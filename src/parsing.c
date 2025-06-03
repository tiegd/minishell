/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/03 16:39:02 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

// Check if the first word is a builtin commande.

int	ft_is_builtin(char *input, int end_word)
{
	int	i;

	i = 0;
	while (i < end_word)
	{
		(void)input;
		// checker si ca correspond à un nom de fonction
		i++;
	}
	return (1);
}

// Check if the first word is a bin commande.

int	ft_is_bin(char *input, int end_word)
{
	int	i;

	i = 0;
	while (i < end_word)
	{
		(void)input;
		// checker si ca correspond à un nom de fonction
		i++;
	}
	return (1);
}

int	ft_str_digit(char *input, int end_word)
{
	int	i;

	i = 0;
	while (i < end_word)
	{
		if (ft_isdigit(input[i]))
			return (1);
		i++;
	}
	return (0);
}

// Check if the command is valide.

// int	ft_check_lst(t_token *lst)
// {
	
// }

/* Convert char *input in char **prompt and
// convert char **prompt in t_token *lst.*/

bool	ft_is_pipe(t_token *lst)
{
	t_token	*tmp;
	int		i;

	tmp = lst;
	while (tmp->next)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '|')
				return (true);
			i++;
		}
		tmp = tmp->next;
	}
	return (false);
}

// int	ft_check_lst(t_token *lst)
// {
// 	if (!ft_is_pipe(lst))
// 		ft_check_lst(lst);
// }

// Test function.

void	ft_print_tab(char **path)
{
	int	i;
	
	i = 0;
	while (i != 12)
	{
		printf(YELLOW"path = %s\n"RESET, path[i]);
		i++;
	}
}

// Check if the firt word is a cmd or anything right.

int	ft_first_word(t_token *input, char **paths)
{
	
}

// Find $(PATH) with getenv(), check if the cmd exist with acces(),
// run the cmd with execve(). 

void	ft_one_cmd(t_token *lst)
{
	t_token	*tmp;
	char	**paths;

	tmp = lst;
	paths = ft_split(getenv("PATH"), ':');
	ft_print_tab(paths);
	if (ft_first_word(tmp, paths))
		return (0);
	tmp = tmp->next;
}

// void	ft_multi_cmd(lst)
// {
	
// }

int	ft_parsing(char *input)
{
	int		i;
	int		len_tab;
	char	**prompt;
	t_token	*lst;

	i = 0;
	len_tab = ft_count_word(input, ' ', '\t');
	prompt = ft_multi_split(input, ' ', '\t');
	while (i < len_tab)
		i++;
	lst = ft_tab_to_lst(prompt, len_tab);
	// ft_check_lst(lst);
	// if (ft_is_pipe(lst))
	// 	ft_multi_cmd(lst);
	// else
		ft_one_cmd(lst);
	return (1);
}
