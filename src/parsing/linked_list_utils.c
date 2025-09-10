/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:54:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/10 18:28:03 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "gblib.h"
#include "minishell.h"

int	count_here_doc(t_token **head, t_gmalloc **gb_head)
{
	t_token	*temp;
	int		count;

	temp = *head;
	count = 0;
	while (temp != NULL)
	{
		if (temp->type == HERE_DOC)
			count++;
		temp = temp->next;
	}
	if (count > 16)
	{
		gb_free_all(gb_head);
		ft_putstr_fd("minishell : maximum here-document count exceeded\n", 2);
		exit(2);
	}
	return (count);
}
