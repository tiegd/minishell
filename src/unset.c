/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:02:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/03 16:38:45 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**unset(char *var, char **old_env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * nb_var(old_env) + 1);
	printf("env size =%d\n", nb_var(old_env));
	while(old_env[i] != NULL)
	{
		if (strcmp_until_char(var, old_env[i], '='))
		{
			if (old_env)
				i++;
			else
				break ;
		}
		new_env[j] = ft_strdup(old_env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	return (new_env);
}
