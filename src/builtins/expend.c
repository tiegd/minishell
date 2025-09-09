/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:18:55 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 08:21:57 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//extrait la variable d'environnement si elle existe, sinon renvoie NULL.

static char	*extract_env(char *temp, char **env, t_gmalloc **head)
{
	int		i;
	char	*extract;

	i = 0;
	while (env[i] != NULL)
	{
		if (strcmp_until_char(temp, env[i], '='))
		{
			extract = env_result(env[i], head);
			return (extract);
		}
		i++;
	}
	return (NULL);
}

static char	*expend_exit_status(char *arg, t_gmalloc **head, t_mini *mini)
{
	char	*res;
	char	*exit_status;
	int		total_len;
	int		i;
	int		j;

	i = 0;
	j = 1;
	exit_status = gb_itoa(mini->exit_status, head);
	total_len = ft_strlen(arg) + ft_strlen(exit_status) - 1;
	res = gb_malloc((total_len + 1) * sizeof(char), head);
	while (exit_status[i])
	{
		res[i] = exit_status[i];
		i++;
	}
	while (arg[j])
		res[i++] = arg[j++];
	res[i] = '\0';
	return (res);
}

char	*expend(char *arg, char **env, t_gmalloc **head, t_mini *mini)
{
	char	*expend;

	while (*arg != '\0' && *arg != '$')
		arg++;
	if (*arg == '$')
		arg++;
	if (!*arg)
		return (NULL);
	if (*arg == '?')
	{
		expend = expend_exit_status(arg, head, mini);
		gfree(arg, head);
		return (expend);
	}
	expend = extract_env(arg, env, head);
	if (!expend)
	{
		expend = gb_malloc(sizeof(char) + 2, head);
		expend[0] = DQ;
		expend[1] = DQ;
		expend[2] = '\0';
	}
	gfree(arg, head);
	return (expend);
}
