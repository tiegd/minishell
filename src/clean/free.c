/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:20:54 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/04 14:06:13 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_split(char **double_tab, int nb_word, t_gmalloc **head)
{
	int	i;

	i = 0;
	while (i < nb_word)
	{
		gfree(double_tab[i], head);
		i++;
	}
	gfree(double_tab, head);
	return (NULL);
}

char	**free_prompt(char **double_tab, t_gmalloc **head)
{
	int	i;

	i = 0;
	if (!*double_tab || !double_tab)
		return (NULL);
	while (double_tab[i] != NULL)
	{
		gfree(double_tab[i], head);
		i++;
	}
	gfree(double_tab, head);
	return (NULL);
}
