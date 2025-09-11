/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dash_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:59:16 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 13:28:36 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Recreating of some environement variable for work correctly :
- PWD : to find out in what directory we are.
- SHLVL : to find out in what level of shell we are. 
- _ : the option of the last simple command.*/

#include "minishell.h"
#include "gblib.h"

char	**env_dash_i(t_gmalloc **head)
{
	int		i;
	char	**new_env;
	char	*pwd;

	i = 0;
	new_env = gb_malloc(sizeof(char *) * 3, head);
	pwd = getcwd(NULL, 0);
	new_env[i] = gb_strjoin_custom("PWD=", pwd, head);
	i++;
	new_env[i] = NULL;
	return (new_env);
}
