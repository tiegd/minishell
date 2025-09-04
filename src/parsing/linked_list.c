/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:01:04 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/04 15:50:37 by jpiquet          ###   ########.fr       */
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
t_token	*ft_lst_addback(t_token *lst, char *s, int len, t_gmalloc **head)
{
	t_token	*new;
	t_token	*last;
	int		i;

	new = gb_malloc(sizeof(t_token), head);
	new->content = gb_malloc((len + 1) * sizeof(char), head);
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

 /* Verifie la commande entré en argument,
 renvoi 1 si c'est un builtin ou 0 si ca ne l'est pas*/
int	is_builtin(char *content)
{
	if (content)
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
	}
	return (0);
}

/*Defini le type de chaques tokens de la liste passé en argument
et rempli la variable "type" de chaque noeud de la liste*/
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
		else
			lst->type = ARGS;
		if (lst->type == HERE_DOC && lst->next != NULL)
		{
			lst->next->type = HERE_DOC;
			lst = lst->next;
		}
		lst = lst->next;
	}
}

// /*Defini le type de chaques tokens de la liste passé en argument
// et rempli la variable "type" de chaque noeud de la liste*/
// void	define_type(t_token *lst)
// {
// 	while (lst != NULL)
// 	{
// 		if (ft_strcmp(lst->content, "|"))
// 			lst->type = PIPE;
// 		else if (ft_strcmp(lst->content, "<"))
// 			lst->type = INPUT;
// 		else if (ft_strcmp(lst->content, ">"))
// 			lst->type = OUTPUT;
// 		else if (ft_strcmp(lst->content, ">>"))
// 			lst->type = APPEND;
// 		else if (ft_strcmp(lst->content, "<<"))
// 			lst->type = HERE_DOC;
// 		else if (ft_strchr(lst->content, '$'))
// 			lst->type = VAR;
// 		else if (ft_strchr(lst->content, '/'))
// 			lst->type = PATH;
// 		else
// 			lst->type = ARGS;
// 		if (lst->type == HERE_DOC)
// 			lst->next->type = HERE_DOC;
// 		lst = lst->next;
// 	}
// }


// Move each element of the prompt in a linked list.
t_token	*ft_tab_to_lst(char **prompt, int len_tab, t_gmalloc **head)
{
	t_token	*lst;
	int		i;
	int		len;
	(void)len_tab;
	
	i = 0;
	lst = NULL;
	while (prompt[i])
	{
		len = ft_strlen(prompt[i]);
		lst = ft_lst_addback(lst, prompt[i], len, head);
		i++;
	}
	// free_prompt(prompt, head);
	define_type(lst);
	return (lst);
}

// // Move each element of the prompt in a linked list.
// t_token	*ft_tab_to_lst(char **prompt, int len_tab, t_gmalloc **head)
// {
// 	t_token	*lst;
// 	int		i;
// 	int		len;
	
// 	i = 0;
// 	lst = NULL;
// 	while (i < len_tab)
// 	{
// 		len = ft_strlen(prompt[i]);
// 		lst = ft_lst_addback(lst, prompt[i], len, head);
// 		i++;
// 	}
// 	define_type(lst);
// 	return (lst);
// }
