/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:18:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/02 19:15:54 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_args(char **args)
{
	if (!args[1]) //regarder si cd possede bien un argument
	{
		ft_putstr_fd("cd : need a relative or absolute path\n", 2);
	}
	else if (nb_var(args) > 2) //regarder si il y a trop d'argument
	{
		ft_putstr_fd("cd : too many arguments\n", 2);
	}
	else
		return (0);
	return (1);
}

void	getcwd_failed(void)
{
	ft_putstr_fd("cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n", 2);
}

void	chdir_failed(char **args, t_mini *mini)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	mini->exit_status = 1;
}

void	cd(char	**args, char **env, t_gmalloc **head, t_mini *mini)
{
	int		i;
	char	*path;
	char	*old_path;
	(void)env;

	i = 0;
	old_path = getcwd(NULL, 0);
	if (!old_path)
		getcwd_failed();
	if (check_args(args))
		mini->exit_status = 1;
	else
	{
		if (args[i + 1][0] != '/' && old_path)
		{
			path = gb_strjoin_custom(old_path, "/", head);
			path = gb_strjoin_custom(path, args[i + 1], head);
		}
		else
			path = gb_strdup(args[i + 1], head);
		if (chdir(path) == -1)
			chdir_failed(args, mini);
	}
	free(old_path);
}
