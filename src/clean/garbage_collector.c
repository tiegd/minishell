/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:34:27 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/24 14:34:34 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_gmalloc	*gmalloc_last(t_gmalloc *lst)
// {
// 	if (lst == NULL)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }

void	gb_free_all(t_gmalloc **head)
{
	t_gmalloc	*temp;

	if (!head || !*head)
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

void	gfree(void *ptr, t_gmalloc **head)
{
	t_gmalloc	*temp;
	t_gmalloc	*prev;

	temp = *head;
	prev = NULL;
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
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	gmalloc_add_back(t_gmalloc **head, t_gmalloc *new)
{
	t_gmalloc	*temp;

	if (!new)
		return ;
	temp = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	*gb_malloc(size_t size, t_gmalloc **lst)
{
	void		*memory;
	t_gmalloc	*new;

	memory = malloc(size);
	if (!memory)
	{
		gb_free_all(lst);
		exit(1);
	}
	new = malloc(sizeof(t_gmalloc));
	if (!new)
	{
		free(memory);
		gb_free_all(lst);
		exit(1);
	}
	new->memory = memory;
	new->next = NULL;
	gmalloc_add_back(lst, new);
	return (memory);
}
