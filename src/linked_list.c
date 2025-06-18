/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:01:04 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/18 10:44:24 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_builtin(char *content)
{
	if (ft_strcmp(content, "echo"))
		return (1);
	if (ft_strcmp(content, "cd"))
		return (1);
	if (ft_strcmp(content, "pwd"))
		return (1);
	if (ft_strcmp(content, "export"))
		return (1);
	if (ft_strcmp(content, "unset"))
		return (1);
	if (ft_strcmp(content, "env"))
		return (1);
	if (ft_strcmp(content, "exit"))
		return (1);
	else
		return (0);
}

void	define_type(t_token *lst)
{
	while (lst != NULL)
	{
		if (ft_strcmp(lst->content, "|"))
			lst->type = PIPE;
		else if (ft_strcmp(lst->content, "<"))
			lst->type = INPUT;
		else if (ft_strcmp(lst->content, ">"))
			lst->type = OUTPUT;
		else if (ft_strcmp(lst->content, ">>"))
			lst->type = APPEND;
		else if (ft_strcmp(lst->content, "<<"))
			lst->type = HERE_DOC;
		else if (ft_strchr(lst->content, '$'))
			lst->type = VAR;
		else if (ft_strchr(lst->content, '/'))
			lst->type = PATH;
		else
		{
			lst->type = ARGS;
		}
		lst = lst->next;
	}
}

// int	define_type(t_token *lst)
// {
// 	while (lst != NULL)
// 	{
// 		if (ft_strcmp(lst->content, "|"))
// 			return (PIPE);
// 		else if (ft_strcmp(lst->content, "<"))
// 			return (INPUT);
// 		else if (ft_strcmp(lst->content, ">"))
// 			return (OUTPUT);
// 		else if (ft_strcmp(lst->content, ">>"))
// 			return (APPEND);
// 		else if (ft_strcmp(lst->content, "<<"))
// 			return (HERE_DOC);
// 		else if (ft_strchr(lst->content, '$'))
// 			return (VAR);
// 		else if (ft_strchr(lst->content, '/'))
// 			return (PATH);
// 		// else if (is_builtin(content))
// 		// 	return (BUILTIN);
// 		else
// 			 (ARGS);
// 		lst = lst->next;
// 	}
// }

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
	define_type(lst);
	// printf("nb_args = %d\n", lst->nb_args);
	// ft_print_lst(lst);
	return (lst);
}
