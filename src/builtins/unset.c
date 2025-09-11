/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:02:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 11:06:35 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "gblib.h"
#include "exec.h"
#include "clean.h"

char	**unset(char *var, char **env, t_gmalloc **head)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = gb_malloc(sizeof(char *) * (nb_var(env) + 1), head);
	while (env[i] != NULL)
	{
		if (env_var_cmp(env[i], var) == 1 || env_var_cmp(var, env[i]) == 2)
		{
			if (env)
				i++;
			else
				break ;
		}
		if (env[i] == NULL)
			break ;
		new_env[j] = gb_strdup(env[i], head);
		i++;
		j++;
	}
	new_env[j] = NULL;
	free_double_tab(env, nb_var(env), head);
	return (new_env);
}

char	**loop_unset(char **env, char **args, t_mini *mini, t_gmalloc **head)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		env = unset(args[i], env, head);
		i++;
	}
	mini->exit_status = 0;
	return (env);
}
