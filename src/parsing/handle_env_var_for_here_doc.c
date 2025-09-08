/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_for_here_doc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:46:13 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/08 12:18:06 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*expend_each_var(char **isolated, char **env,
							t_gmalloc **head, t_mini *mini)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (isolated[i])
	{
		if (ft_strchr(isolated[i], '$'))
		{
			isolated[i] = expend(isolated[i], env, head, mini);
			index++;
		}
		i++;
	}
	return (isolated);
}

static char	*join_parts(char **str_tab, t_gmalloc **head)
{
	int		i;
	char	*res;

	i = 0;
	res = gb_malloc(sizeof(char), head);
	res[0] = '\0';
	while (str_tab[i])
	{
		res = gb_strjoin_custom(res, str_tab[i], head);
		i++;
	}
	return (res);
}

char	*handle_env_var_for_here_doc(char *prompt, t_mini *mini)
{
	char	**isolated;
	char	*final;

	isolated = split_parts(prompt, &mini->gmalloc);
	isolated = expend_each_var(isolated, mini->env, &mini->gmalloc, mini);
	if (!isolated)
		return (NULL);
	final = join_parts(isolated, &mini->gmalloc);
	gfree(isolated, &mini->gmalloc);
	return (final);
}
