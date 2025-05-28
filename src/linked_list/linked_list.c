/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:01:04 by gaducurt          #+#    #+#             */
/*   Updated: 2025/05/28 10:55:44 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lst_last(t_token *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lst_addback(t_token *lst, char *s, int len)
{
	t_token	*new;
	t_token	*last;
	int		i;

	new = malloc(sizeof(t_list));
	if (!new)
		return (ft_lstfree(lst));
	new->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new->content)
	{
		free(new);
		return (ft_lstfree(lst));
	}
	i = -1;
	while (++i < len)
		new->content[i] = s[i];
	new->content[i] = '\0';
	new->next = NULL;
	if (!lst)
	{
		lst = new;
		return ;
	}
	last = ft_lstlast(lst);
	last->next = new;
}

t_token	*ft_tab_to_lst(t_token *lst, char **prompt, int len_tab)
{
	t_token	*lst;
	int		i;
	
	i = 0;
	while (i < len_tab)
	{
		ft_lst_addback(lst, prompt[i], len_tab);
		i++;
	}
	return (lst);
}
