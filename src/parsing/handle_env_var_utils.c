/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:46:13 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 13:45:24 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "gblib.h"

static int	count_part_to_join(char	*prompt)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (prompt[i])
	{
		if (prompt[i] == '$')
		{
			count++;
			while (prompt[i] && exp_isalnum(prompt[i]))
				i++;
			count++;
		}
		if (prompt[i] == '\0')
			break ;
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
	while (str[*i] && exp_isalnum_question_mark(str[*i]))
		(*i)++;
	if (*i > start)
	{
		variable = gb_substr(str, start, *i - start, head);
		return (variable);
	}
	return (NULL);
}

char	**split_parts(char *prompt, t_gmalloc **head)
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
		{
			parts[index++] = extract;
		}
		extract = extract_variable(prompt, &i, head);
		if (extract)
		{
			parts[index++] = extract;
		}
	}
	parts[index] = NULL;
	return (parts);
}
