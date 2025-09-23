/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:21:24 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 13:25:07 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "gblib.h"
#include "builtins.h"

// Count the number of strings in a char**.

int	nb_var(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		i++;
	}
	return (i);
}

/*Duplicate the environement variable passed in params en return a char**
or NULL if there is an erreor.*/

static char	**envdup(char **old_env, t_gmalloc **head)
{
	int		i;
	int		env_len;
	char	**new_env;

	i = 0;
	env_len = nb_var(old_env);
	new_env = gb_malloc(sizeof(char *) * (env_len + 2), head);
	while (old_env[i] != NULL)
	{
		new_env[i] = gb_strdup(old_env[i], head);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

/*Extract environement variable and duplicate in a new string tab.
We replace it if it aleardy exists.*/

char	**ft_export(char **env, char *new_var, t_mini *mini, t_gmalloc **head)
{
	int		i;
	char	**new_env;

	if (!is_valid_identifier(new_var, mini))
		return (env);
	new_env = envdup(env, head);
	i = 0;
	while (new_env[i])
	{
		if (handle_same_var(new_var, new_env, i, head))
			return (new_env);
		i++;
	}
	i = nb_var(env);
	new_env[i] = gb_strdup(new_var, head);
	new_env[i + 1] = NULL;
	gfree(new_var, head);
	return (new_env);
}

/*Expend if there is '$' in teh variable environement
and check if it alreday to know if we need to add it to env.*/

char	**loop_export(char **env, char **args, t_mini *mini, t_gmalloc **head)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		env = ft_export(env, args[i], mini, head);
		i++;
	}
	mini->exit_status = 0;
	return (env);
}
