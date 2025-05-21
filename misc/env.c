/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:54:14 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/20 17:10:40 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int len_env(char ** envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return i;
}

int main(int argc, char **argv, char **envp)
{
	char **env_out;
	int i;

	int len = len_env(envp);
	printf("nb ligne de env = %d\n", len);
	env_out = malloc(sizeof(char *) * len);
	for (i = 0; envp[i] != NULL; i++)
	{
		env_out[i] = strdup(envp[i]);
	}
	for (i = 0; envp[i] != NULL; i++)
	{
		printf("ORIGiNAL == %s\n", env_out[i]);
		printf("OUT == %s\n", env_out[i]);
	}
	if (argv[1])
	return 0;
}