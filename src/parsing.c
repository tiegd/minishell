/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/02 10:59:15 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// Check the index of the end of the first word.

int	ft_borne_first(char *input)
{
	int	i;

	i = 0;
	while (input[i] != ' ' || input[i] != '\t' || input[i])
		i++;
	if (input[i] == ' ' || input[i] == '\t')
	{
		while (input[i] != ' ' || input[i] != '\t' || input[i])
			i++;
	}
	return (i);
}

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

// Before any malloc, doing some basics checks on the frst word.

int	ft_first_word(char *input)
{
	int	end_first;

	end_first = ft_borne_first(input);
	if (end_first == 0)
		return (0);
	if (ft_str_digit(input, end_first))
		return (0);
	if (ft_is_builtin(input, end_first) || ft_is_bin(input, end_first))
		return (1);
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

	tmp = lst;
	while (tmp->next)
	{
		if (tmp->content == '|')
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

// int	ft_check_lst(t_token *lst)
// {
// 	if (!ft_is_pipe(lst))
// 		ft_check_lst(lst);
// }

void	ft_one_cmd(lst)
{
	if (lst )
}

void	ft_multi_cmd(lst)
{
	
}

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
	if (ft_is_pipe(lst))
		ft_multi_cmd(lst);
	else
		ft_one_cmd(lst);
	return (1);
}
