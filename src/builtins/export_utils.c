/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:50:19 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 13:02:01 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "clean.h"
#include "gblib.h"

/*Compare the name of two environemnt variables*/

int	env_var_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (i > 1 && s1[i - 1] - s2[i - 1] == 0 && s1[i] - s2[i] == 0)
		return (1);
	else if (i > 1 && s1[i - 1] - s2[i - 1] == 0
		&& s1[i] == '\0' && s2[i] == '=')
		return (2);
	return (0);
}

int	is_valid_identifier(char *variable, t_mini *mini)
{
	int	i;

	i = 0;
	if (ft_isdigit(variable[0]) || !exp_isalnum(variable[0]))
	{
		mini->exit_status = 1;
		print_not_valid_identifier(variable);
		return (0);
	}
	while (variable[i] && variable[i] != '=')
	{
		if (!exp_isalnum(variable[i]))
		{
			mini->exit_status = 1;
			print_not_valid_identifier(variable);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_empty_var(char *variable)
{
	int	i;

	i = 0;
	while (variable[i])
	{
		if (variable[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	replace_same_var(char *new_var, char **new_env, int i, t_gmalloc **head)
{
	if (!is_empty_var(new_var))
	{
		gfree(new_env[i], head);
		new_env[i] = gb_strdup(new_var, head);
	}
	gfree(new_var, head);
}

int	handle_same_var(char *new_var, char **new_env, int i, t_gmalloc **head)
{
	if (env_var_cmp(new_env[i], new_var) == 1
		|| env_var_cmp(new_env[i], new_var) == 2)
	{
		replace_same_var(new_var, new_env, i, head);
		return (1);
	}
	else if (env_var_cmp(new_var, new_env[i]) == 2)
	{
		gfree(new_var, head);
		return (1);
	}
	return (0);
}
