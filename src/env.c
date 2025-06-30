/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:21:09 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/30 16:46:00 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//recuperer la variable d'environnement et la print dans le fd passsé en paramètre.
void	ft_env(char **env, int fd)
{
	int	i;

	i = 0;
	// ft_print_tab(env);
	if (!env)
	{
		perror("env doesn´t exist");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("error with dup2");
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	// if (env[i] == NULL)
	// 	printf("%s\n",env[i]);
}
