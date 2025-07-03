/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:46:13 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/02 15:29:40 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_part_to_join(char	*prompt)
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

char	*extract_text(char *str, int *i)
{
	int		start;
	char	*text;
	
	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	if (*i > start)
	{
		text = ft_substr(str, start, *i - start);
		if (!text)
			return (NULL);
		return (text);
	}
	return (NULL);
}

char	*extract_variable(char *str, int *i)
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
		variable = ft_substr(str, start, *i - start);
		if (!variable)
			return (NULL);
		return (variable);
	}
	return (NULL);
}

char	**split_parts(char *prompt)
{
	int		i;
	int		index;
	char	**parts;
	char	*extract;

	i = 0;
	index = 0;
	parts = malloc(sizeof(char *) * (count_part_to_join(prompt) + 2));
	if (!parts)
		return (NULL);
	while (prompt[i])
	{
		extract = extract_text(prompt, &i);
		if (extract)
			parts[index++] = extract;
		extract = extract_variable(prompt, &i);
		if (extract)
			parts[index++] = extract;
	}
	parts[index] = NULL;
	return (parts);
}

void	*expend_each_var(char **isolated, char **env, int *quote_dollars, bool *malloc_error)
{
	int		i;
	int 	index;

	i = 0;
	index = 0;
	while(isolated[i])
	{
		if (strchr(isolated[i], '$'))
		{
			if (quote_dollars[index] == DQ)
			{
				isolated[i] = expend(isolated[i], env);
				if (!isolated[i] && (*malloc_error) == true)
				{
					free_all(isolated);
					return (NULL);
				}
			}
			index++;
		}
		i++;
	}
	return (isolated);
}

// void	*expend_each_var(char **isolated, char **env, int *quote_dollars, bool *malloc_error)
// {
// 	int		i;
// 	int 	index;

// 	i = 0;
// 	index = 0;
// 	while(isolated[i])
// 	{
// 		if (strchr(isolated[i], '$') && quote_dollars[index] == DQ)
// 		{
// 			isolated[i] = expend(isolated[i], env);
// 			if (!isolated[i] && (*malloc_error) == true)
// 			{
// 				free_all(isolated);
// 				return (NULL);
// 			}
// 			index++;
// 		}
// 		i++;
// 	}
// 	return (isolated);
// }

int	count_dollars(char *prompt)
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

int	check_dollar_existence(char *prompt, int *i, char quote)
{
	int	res;

	res = 0;
	(*i)++;
	while(prompt[*i] && prompt[*i] != quote)
	{
		if (prompt[*i] == '$')
			res = 1;
		(*i)++;
	}
	if (prompt[*i] == quote)
		(*i)++;
	return (res);
}

int	which_quote(char *prompt, int *index)
{
	while (prompt[*index])
	{
		if (prompt[*index] == '$')
		{
			(*index)++;
			return (DQ);
		}
		if (prompt[*index] == DQ && check_dollar_existence(prompt, index, DQ))
			return (DQ);
		if (prompt[*index] == SQ && check_dollar_existence(prompt, index, SQ))
			return (SQ);
		(*index)++;
	}
	return (DQ);
}

int	*fill_tab_quote(char *prompt)
{
	int	i;
	int index;
	int dollars;
	int	*tab;

	i = 0;
	index = 0;
	dollars = count_dollars(prompt);
	tab = malloc(sizeof(int) * dollars);
	while (i < dollars)
	{
		tab[i] = which_quote(prompt, &index);
		i++;	
	}
	return (tab);
}

char	*join_parts(char **str_tab)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_calloc(1, sizeof(char));
	while (str_tab[i])
	{
		res = ft_strjoin_custom(res, str_tab[i]);
		if (!res)
		{
			free(res);
			return (NULL);
		}
		i++;
	}
	return (res);
}

char	*handle_env_var(char *prompt, char **env)
{
	char 	**isolated;
	char	*final;
	int		*quote_dollars;
	bool	malloc_error;

	malloc_error = false;
	isolated = split_parts(prompt);
	print_tab_char(isolated);
	if (!isolated)
		return (NULL);
	quote_dollars = fill_tab_quote(prompt);
	print_tab_int(quote_dollars);
	isolated = expend_each_var(isolated, env, quote_dollars, &malloc_error);
	if (!isolated)
		return (NULL);
	free(quote_dollars);
	final = join_parts(isolated);
	if (!final)
	{
		free_all(isolated);
		return (NULL);
	}
	return (final);
}
