/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:01:04 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/10 15:11:44 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free all of the list.

void	ft_lstfree(t_token *lst)
{
	t_token	*buffer;

	if (lst)
	{
		while (lst)
		{
			buffer = lst->next;
			free(lst->content);
			free(lst);
			lst = buffer;
		}
	}
}

// Find the last node of the list.

t_token	*ft_lst_last(t_token *lst)
{
	if (!lst || !lst->next)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// Add the new node at the end of the list.

t_token	*ft_lst_addback(t_token *lst, char *s, int len)
{
	t_token	*new;
	t_token	*last;
	int		i;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		ft_lstfree(lst);
		return NULL;
	}
	new->content = malloc((len + 1) * sizeof(char));
	if (!new->content)
	{
		free(new);
		ft_lstfree(lst);
		return NULL;
	}
	i = -1;
	while (++i < len)
		new->content[i] = s[i];
	new->content[i] = '\0';
	new->next = NULL;
	if (!lst)
		lst = new;
	else
	{
		last = ft_lst_last(lst);
		last->next = new;
	}
	return (lst);
}

// Just for test the list. This function will be deleted.

void	ft_print_lst(t_token *lst)
{
	while (lst)
	{
		printf(RED"content = %s\n"RESET, lst->content);
		lst = lst->next;
	}
}

// Move each element of the prompt in a linked list.

t_token	*ft_tab_to_lst(char **prompt, int len_tab)
{
	t_token	*lst;
	int		i;
	int		len;
	
	i = 0;
	lst = NULL;
	while (i < len_tab)
	{
		len = ft_strlen(prompt[i]);
		lst = ft_lst_addback(lst, prompt[i], len);
		i++;
	}
	ft_print_lst(lst);
	return (lst);
}
