/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:01:04 by gaducurt          #+#    #+#             */
/*   Updated: 2025/05/28 16:47:32 by gaducurt         ###   ########.fr       */
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

void	ft_lst_addback(t_token *lst, char *s, int len)
{
	t_token	*new;
	t_token	*last;
	int		i;

	new = malloc(sizeof(t_token));
	if (!new)
		return (ft_lstfree(lst));
	new->content = malloc((len + 1) * sizeof(char));
	if (!new->content)
	{
		free(new);
		return (ft_lstfree(lst));
	}
	i = -1;
	printf(RED"s = %s\n"RESET, s);
	printf(MAGENTA"len = %d\n"RESET, len);
	while (++i < len)
	{
		new->content[i] = s[i];
		printf(YELLOW"new->content[i] = %c\n"RESET, new->content[i]);
		printf("i boucle = %d\n", i);
	}
	new->content[i] = '\0';
	new->next = NULL;
	printf(YELLOW"new->content[i] = %c\n"RESET, new->content[i]);
	printf("i boucle = %d\n", i);
	if (!lst)
	{
		lst = new;
		return ;
	}
	else
	{
		last = ft_lst_last(lst);
		last->next = new;
	}
	printf(GREEN"new->content = %s\n"RESET, new->content);
	printf("continue\n");
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
	lst = malloc(sizeof(t_token));
	while (i < len_tab)
	{
		len = ft_strlen(prompt[i]);
		printf(CYAN"len = %d\n"RESET, len);
		ft_lst_addback(lst, prompt[i], len);
		i++;
		printf("i = %d\n", i);
	}
	ft_print_lst(lst);
	return (lst);
}
