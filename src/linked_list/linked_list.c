/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:01:04 by gaducurt          #+#    #+#             */
/*   Updated: 2025/05/26 13:01:31 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_lst_last(t_cmd *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lst_addback(t_cmd *lst, char *s, int len)
{
	t_cmd	*new;
	t_cmd	*last;
	int		i;

	new = malloc(sizeof(t_list));
	if (!new)
		return (ft_lstfree(lst));
	new->token = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new->token)
	{
		free(new);
		return (ft_lstfree(lst));
	}
	i = -1;
	while (++i < len)
		new->token[i] = s[i];
	new->token[i] = '\0';
	new->next = NULL;
	if (!lst)
	{
		lst = new;
		return ;
	}
	last = ft_lstlast(lst);
	last->next = new;
}