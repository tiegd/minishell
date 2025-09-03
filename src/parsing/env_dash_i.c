/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dash_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:59:16 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/03 17:13:40 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*bash recréer certaines variable d'environnement pour pouvoir fonctionner :

- "PWD" (getcwd) pour savoir ou est ce qu'on se situe
- "SHLVL" pour savoir a quel niveau du shell on se situe
- "_" qui represente la dernière commande qu'on a fait*/

#include "minishell.h"

char	**env_dash_i(t_gmalloc **head)
{
	int		i;
	char	**new_env;
	char	*pwd;

	i = 0;
	new_env = malloc(sizeof(char *) * 3);
	if (!new_env)
		return (NULL);
	pwd = getcwd(NULL, 0);
	new_env[i] = gb_strjoin_custom("PWD=", pwd, head);
	i++;
	new_env[i] = NULL;
	return (new_env);
}
