/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_to_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:22:29 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/08 18:25:47 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*one_line_path(char **paths, t_gmalloc **head)
{
	char	*new_tab;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	while (paths[0][i] && count <= 2)
	{
		if (paths[0][i] == '/')
			count++;
		if (count <= 2)
			i++;
	}
	new_tab = gb_malloc((i + 1) * sizeof (char), head);
	while (j < i)
	{
		new_tab[j] = paths[0][j];
		j++;
	}
	new_tab[j] = '\0';
	return (new_tab);
}

char	**is_home(char **paths, t_gmalloc **head)
{
	char	**new_tab;

	new_tab = gb_malloc(2 * sizeof(char *), head);
	new_tab[0] = one_line_path(paths, head);
	new_tab[1] = NULL;
	return (new_tab);
}

// Add the cmd at the end of each path.

char	**ft_add_cmd(char **paths, int nb_path, t_cmd *cmd, t_gmalloc **head)
{
	char	**new_tab;
	int		i;

	i = 0;
	if (cmd->args[0][0] == '~' && cmd->args[0][1] == '\0')
		new_tab = is_home(paths, head);
	else
	{
		new_tab = gb_malloc(((nb_path + 1) * sizeof(char *)), head);
		new_tab[nb_path] = NULL;
		while (paths[i] != NULL)
		{
			new_tab[i] = gb_strjoin(paths[i], "/", head);
			new_tab[i] = gb_strjoin_custom(new_tab[i], cmd->args[0], head);
			i++;
		}
	}
	free_prompt(paths, head);
	return (new_tab);
}

int	ft_nb_path(char **path)
{
	int	i;

	i = 0;
	if (!path)
		return (i);
	while (path[i] != NULL)
		i++;
	return (i);
}
