/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:00:33 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 13:05:57 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "gblib.h"
#include "builtins.h"

void	update_pwd(t_mini *mini, t_gmalloc **head)
{
	char	*new_pwd;
	char	*final;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	final = gb_strjoin("PWD=", new_pwd, head);
	free(new_pwd);
	mini->env = ft_export(mini->env, final, mini, head);
}

void	update_oldpwd(char *old_path, t_mini *mini, t_gmalloc **head)
{
	char	*final;

	if (!old_path)
		return ;
	final = gb_strjoin("OLDPWD=", old_path, head);
	free(old_path);
	mini->env = ft_export(mini->env, final, mini, head);
}
