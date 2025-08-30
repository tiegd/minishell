/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:21:09 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/28 19:45:29 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//recuperer la variable d'environnement et la print dans le fd passsé en paramètre.
void	ft_env(char **env, int fd)
{
	int	i;

	i = 0;
	// if (!env)
	// {
	// 	perror("env doesn´t exist");
	// 	return ;
	// }
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("error with dup2");
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	// if (env[i] == NULL)
	// 	printf("%s\n",env[i]);
}
