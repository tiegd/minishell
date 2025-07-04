/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:34:27 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/04 09:41:46 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gmalloc	*gmalloc_last(t_gmalloc *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	gb_free_all(t_gmalloc **head)
{
	t_gmalloc	*temp;

	if (*head == NULL)
		return ;
	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		if (temp->memory)
			free(temp->memory);
		free(temp);
	}
}

void	gfree(t_gmalloc **head, void *ptr)
{
	t_gmalloc	*temp;
	t_gmalloc	*prev;

	temp = *head;
	prev = NULL;
	if (*head == NULL)
		return ;
	while (temp)
	{
		if (temp->memory == ptr)
		{
			if (prev == NULL)
				*head = temp->next;
			else
				prev->next = temp->next;
			free(temp->memory);
			free(temp);
		}
		prev = temp;
		temp = temp->next;
	}
}

void	gmalloc_add_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = gmalloc_last(*lst);
	temp->next = new;
}

void	*gb_malloc(size_t size, t_gmalloc *lst)
{
	void		*memory;
	t_gmalloc	*new;

	memory = malloc(size);
	if (!memory)
	{
		gb_free_all(&lst);
		exit(1);
	}
	new = malloc(sizeof(t_gmalloc));
	if (!new)
	{
		free(memory);
		gb_free_all(&lst);
		exit(1);
	}
	new->memory = memory;
	gmalloc_add_back(&lst, new);
	return (memory);
}
