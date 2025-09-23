/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:28:59 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/23 14:15:58 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "gblib.h"
#include "exec.h"
#include "parsing.h"

static char	*ft_path_line(char **env, t_gmalloc **head)
{
	int		i;
	int		j;
	int		len;
	char	*path;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			j = 0;
			len = ft_strlen(env[i]) - 5;
			path = gb_malloc(((len + 1) * sizeof(char)), head);
			while (env[i][j + 5])
			{
				path[j] = env[i][j + 5];
				j++;
			}
			path[j] = '\0';
			return (path);
		}
		i++;
	}
	return (NULL);
}

/*Extract the $PATH in env to a char**, return 1 if an array of PATH has
been found or 0 if PATH can´t be found + copy the cmd into pathname.*/

int	extract_path(t_cmd *cmd, t_mini *mini, t_gmalloc **head)
{
	char	*line;
	int		nb_path;

	line = ft_path_line(mini->env, head);
	if (!line)
	{
		if (manage_error_exec(mini->cmd, mini) == 1)
			return (0);
		cmd->pathname = cmd->args[0];
		return (2);
	}
	cmd->paths = gb_split(line, ':', head);
	nb_path = ft_nb_path(cmd->paths);
	if (cmd->args[0])
	{
		cmd->paths = ft_add_cmd(cmd->paths, nb_path, cmd, head);
		if (manage_error_exec(mini->cmd, mini) == 1)
			return (0);
	}
	return (1);
}
