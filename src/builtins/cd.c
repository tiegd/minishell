/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:18:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/22 12:02:22 by jpiquet          ###   ########.fr       */
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

void	cd(char	**args, char **env, t_gmalloc **head, t_mini *mini)
{
	int		i;
	char	*path;
	char	*old_path;
	(void)mini;
	(void)env;

	i = 0;
	old_path = getcwd(NULL, 0);
	if (!args[i + 1]) //regarder si cd possede bien un argument
	{
		ft_putstr_fd("cd : need a relative or absolute path\n", 2);
		mini->exit_status = 1;
		return ;
	}
	if (args[i] && nb_var(args) == 1) //regarder si la commande entré est uniquement cd sans arguments.
	{
		path = expend("$HOME", env, head, mini);
		if (path[0] == '\0')
		{
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": HOME not set", 2);
		}
		if (chdir(path) == -1)
		{
			free(path);
			perror("error with chdir");
		}
		free(path);
	}
	else if (!is_opt_cd(args[i + 1]) && nb_var(args) > 3) //regarder si il y a trop d'argument
	{
		ft_putstr_fd("cd : too many arguments\n", 2);
		return ;
	}
	else
	{
		if (args[i + 1][0] != '/')
		{
			path = gb_strjoin_custom(old_path, "/", head);
			path = gb_strjoin_custom(path, args[i + 1], head);
		}
		else
			path = gb_strdup(args[i + 1], head);
		if (chdir(path) == -1)
		{
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(" : No such file or directory\n", 2);
		}
	}
	// old_path = ft_strjoin("OLDPWD=", old_path);
	// env = ft_export(env, old_path, head);
	// if (!path)
	// 	free(path);
}
