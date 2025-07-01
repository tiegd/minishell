/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:18:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/01 11:01:20 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_opt_cd(char	*option)
{
	if (ft_strcmp(option, "-P"))
		return (1);
	else if (ft_strcmp(option, "-L"))
		return (1);
	else
		return (0);
}

void	cd(char	**args, char **env, bool malloc_error)
{
	int		i;
	char	*path;
	char	*old_path;

	i = 0;

	path = NULL;
	old_path = getcwd(NULL, 0);
	if (!args || !ft_strcmp(args[i], "cd")) //regarder si args existe et si le 1er argument est bien cd 
		return ;
	if (args[i] && nb_var(args) == 1) //regarder si la commande entré est uniquement cd sans arguments.
	{
		path = expend("$HOME", env, malloc_error);
		if (!path && malloc_error == false)
		{
			free(path);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": HOME not set", 2);
		}
		// printf("path $HOME = %s\n", path);
		if (chdir(path) == -1)
		{
			free(path);
			perror("error with chdir");
		}
		free(path);
	}
	else if (!is_opt_cd(args[i + 1]) && nb_var(args) > 3) //regarder si il y a trop d'argument
	{
		ft_putstr_fd("cd : too many arguments", 2);
		return ;
	}
	else if (args[i] && args[i + 1][0] == '-' && args[i + 1][1] == '\0') //regarder si l'option est - 
	{
		path = expend("$OLDPWD", env, malloc_error);
		// printf("path $OLDPWD = %s\n", path);
		if (!path && malloc_error == false)
		{
			free(path);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": OLDPWD not set\n", 2);
		}
		if (chdir(path) == -1)
		{
			perror("error with chdir");
			free(path);
		}
		pwd(1);
		free(path);
	}
	else
	{
		// printf("args[i + 1] = %s\n", args[i + 1]);
		if (chdir(args[i + 1]) == -1)
		{
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(" : No such file or directory\n", 2);
			// ft_putstr_fd(args[i + 1], 2);
		}
	}
	old_path = ft_strjoin("OLDPWD=", old_path);
	env = ft_export(env, old_path);
	// if (!path)
	// 	free(path);
}
