/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:18:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/28 16:19:23 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_opt_cd(char	*option)
{
	if (ft_strcmp(option, "-P"))
		return (1);
	if (ft_strcmp(option, "-L"))
		return (1);
	else
		return (0);
}

void	cd(char	**args, char **env, bool malloc_error)
{
	int	i;

	i = 0;
	if (!args || ft_strcmp(args[i], "cd")) //regarder si args existe et si le 1er argument est bien cd 
		return ;
	if (is_opt_cd(args[i + 1]) && args[i + 2] != NULL) //regarder si il y a trop d'argument
	{
		ft_putstr_fd("cd : too many arguments", 2);
		return ;
	}
	if (args[i] && !args[i + 1]) //regarder si la commande entré est uniquement cd sans arguments.
	{
		if (chdir(expend("$HOME", env, malloc_error)) == -1)
			perror("error with chdir");
	}
	else if (args[i] && args[i + 1][0] == '-' && args[i + 1][1] == '\0') //regarder si l'option est - 
	{
		if (chdir(expend("$OLDPWD", env, malloc_error)) - 1)
			perror("error with chdir");
	}
	else
		if (chdir(args[i + 1]) == -1)
		{
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(" : No such file or directory", 2);
		}
}