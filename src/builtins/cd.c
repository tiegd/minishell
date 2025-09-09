/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:18:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 09:38:00 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args(char **args)
{
	if (!args[1])
	{
		ft_putstr_fd("cd : need a relative or absolute path\n", 2);
	}
	else if (nb_var(args) > 2)
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

void	update_pwd(t_mini *mini, t_gmalloc **head)
{
	char	*new_pwd;
	char	*final;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	final = gb_strjoin("PWD=", new_pwd, head);
	gfree(new_pwd, head);
	ft_export(mini->env, final, mini, head);
}

void	cd(char	**args, t_gmalloc **head, t_mini *mini)
{
	int		i;
	char	*path;
	char	*old_path;

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
	update_pwd(mini, head);
	free(old_path);
}
