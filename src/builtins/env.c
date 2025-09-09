/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:21:09 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 08:21:16 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*recuperer la variable d'environnement et la print dans 
le fd passsé en paramètre.*/

void	ft_env(char **env, int fd, t_mini *mini)
{
	int	i;

	i = 0;
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("error with dup2");
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	mini->exit_status = 0;
}
