/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/05/26 13:01:40 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_cmd	*ft_tab_to_lst(t_cmd *lst, char **prompt, int len_tab)
{
	int		i;
	
	i = 0;
	while (i < len_tab)
	{
		ft_lst_addback(lst, prompt[i], len_tab);
	}
}

int	ft_check_prompt(char *input)
{
	int		i;
	int		len_tab;
	char	**prompt;
	t_cmd	*lst;

	i = 0;
	len_tab = ft_count_word(input, ' ', '\t');
	printf("len_tab = %d\n", len_tab);
	prompt = ft_multi_split(input, ' ', '\t');
	while (i < len_tab)
	{
		printf("prompt[%d] = %s\n", i, prompt[i]);
		i++;
	}
	lst = ft_tab_to_lst(lst, prompt, len_tab);
	return (1);
}
