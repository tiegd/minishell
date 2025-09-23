/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:46:13 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 13:46:01 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "builtins.h"
#include "gblib.h"

void	*expend_each_var(char **isolated, char **env,
						int *quote_dollars, t_mini *mini)
{
	int	i;
	int	index;
	int	j;

	i = 0;
	j = 0;
	index = 0;
	while (isolated[i])
	{
		if (ft_strchr(isolated[i], '$'))
		{
			if (quote_dollars[index] == DQ && !is_eof(isolated[i - j])
				&& !is_alone(isolated, i))
			{
				isolated[i] = expend(isolated[i], env, &mini->gmalloc, mini);
			}
			index++;
		}
		i++;
		j = 1;
	}
	return (isolated);
}

static int	count_dollars(char *prompt)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (prompt[i])
	{
		if (prompt[i] == '$')
			count++;
		i++;
	}
	return (count);
}

static int	*fill_tab_quote(char *prompt, t_gmalloc **head)
{
	int	i;
	int	index;
	int	dollars;
	int	*tab;

	i = 0;
	index = 0;
	dollars = count_dollars(prompt);
	tab = gb_malloc(sizeof(int) * dollars, head);
	while (i < dollars)
	{
		tab[i] = which_quote(prompt, &index);
		i++;
	}
	return (tab);
}

char	*join_parts(char **str_tab, int len_array, t_gmalloc **head)
{
	int		i;
	char	*res;

	i = 0;
	res = gb_malloc(sizeof(char), head);
	res[0] = '\0';
	while (i < len_array)
	{
		res = gb_strjoin_custom(res, str_tab[i], head);
		i++;
	}
	gfree(str_tab, head);
	return (res);
}

char	*handle_env_var(char *prompt, t_mini *mini)
{
	char	**isolated;
	char	*final;
	int		*quote_dollars;
	int		len_array;

	isolated = split_parts(prompt, &mini->gmalloc);
	len_array = count_tab(isolated);
	quote_dollars = fill_tab_quote(prompt, &mini->gmalloc);
	isolated = expend_each_var(isolated, mini->env, quote_dollars, mini);
	gfree(quote_dollars, &mini->gmalloc);
	if (!isolated)
		return (NULL);
	final = join_parts(isolated, len_array, &mini->gmalloc);
	return (final);
}
