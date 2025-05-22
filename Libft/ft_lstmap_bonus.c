/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:48:12 by jpiquet           #+#    #+#             */
/*   Updated: 2025/01/14 15:18:02 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_element;
	t_list	*new_list;
	void	*content_temp;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_list = NULL;
	while (lst != NULL)
	{
		content_temp = f(lst->content);
		new_element = ft_lstnew(content_temp);
		if (new_element == NULL)
		{
			del(content_temp);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_element);
		lst = lst->next;
	}
	return (new_list);
}
