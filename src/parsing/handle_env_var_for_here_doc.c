/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_for_here_doc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:46:13 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/27 10:16:28 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_part_to_join(char	*prompt)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(prompt[i])
	{
		if (prompt[i] == '$')
		{
			count++;
			while (prompt[i] && exp_isalnum(prompt[i]))
				i++;
			count++;
		}
		if (prompt[i] == '\0')
			break;
		i++;
	}
	return (count);
}

static char	*extract_text(char *str, int *i, t_gmalloc **head)
{
	int		start;
	char	*text;
	
	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	if (*i > start)
	{
		text = gb_substr(str, start, *i - start, head);
		return (text);
	}
	return (NULL);
}

static char	*extract_variable(char *str, int *i, t_gmalloc **head)
{
	int		start;
	char	*variable;

	start = *i;
	if (str[*i] == '$')
		(*i)++;
	while (str[*i] && exp_isalnum(str[*i]))
		(*i)++;
	if (*i > start)
	{
		variable = gb_substr(str, start, *i - start, head);
		return (variable);
	}
	return (NULL);
}

static char	**split_parts(char *prompt, t_gmalloc **head)
{
	int		i;
	int		index;
	char	**parts;
	char	*extract;

	i = 0;
	index = 0;
	parts = gb_malloc(sizeof(char *) * (count_part_to_join(prompt) + 2), head);
	while (prompt[i])
	{
		extract = extract_text(prompt, &i, head);
		if (extract)
			parts[index++] = extract;
		extract = extract_variable(prompt, &i, head);
		if (extract)
			parts[index++] = extract;
	}
	parts[index] = NULL;
	return (parts);
}

static void	*expend_each_var(char **isolated, char **env, t_gmalloc **head, t_mini *mini)
{
	int		i;
	int 	index;

	i = 0;
	index = 0;
	while(isolated[i])
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
	char 	**isolated;
	char	*final;

	isolated = split_parts(prompt, &mini->gmalloc);
	isolated = expend_each_var(isolated, mini->env, &mini->gmalloc, mini);
	if (!isolated)
		return (NULL);
	final = join_parts(isolated, &mini->gmalloc);
	gfree(isolated, &mini->gmalloc);
	return (final);
}
