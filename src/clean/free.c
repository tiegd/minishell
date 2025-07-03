/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:20:54 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/27 16:21:20 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_split(char **double_tab, int nb_word)
{
	int	i;

	i = 0;
	while (i < nb_word)
	{
		free(double_tab[i]);
		i++;
	}
	free(double_tab);
	return (NULL);
}
