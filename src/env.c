/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:21:09 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/23 14:45:49 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **env, int fd)
{
	int	i;

	i = 0;
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("error with dup2");
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}