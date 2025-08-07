/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_for_here_doc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:46:13 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/07 14:28:16 by gaducurt         ###   ########.fr       */
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

// /*creer une fonction qui va faire en sorte de checker si l'argument avant est un <<*/
// int	is_eof(char	*prev)
// {
// 	int	i;
// 	bool here_doc;

// 	i = 0;
// 	here_doc = false;
// 	while (prev[i])
// 	{
// 		while (prev[i] && (is_ws(prev[i]) || exp_isalnum(prev[i])))
// 			i++;
// 		if (is_here_doc(prev[i], prev[i + 1]))
// 		{
// 			here_doc = true;
// 			i += 2;
// 		}
// 		else
// 			i++;
// 		while (prev[i] && (is_quote(prev[i]) || is_ws(prev[i])))
// 		{
// 			if (!is_quote(prev[i]) && !is_ws(prev[i]))
// 				return(0);
// 			i++;
// 		}
// 	}
// 	if (here_doc == true)
// 		return (1);
// 	return (0);
// }

static void	*expend_each_var(char **isolated, char **env, t_gmalloc **head, t_mini *mini)
{
	int		i;
	int 	index;

	i = 0;
	index = 0;
	while(isolated[i])
	{
		if (strchr(isolated[i], '$'))
		{
			isolated[i] = expend(isolated[i], env, head, mini);
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

// int	count_dollars(char *prompt)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (prompt[i])
// 	{
// 		if (prompt[i] == '$')
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// int	check_dollar_existence(char *prompt, int *i, char quote)
// {
// 	int	res;

// 	res = 0;
// 	(*i)++;
// 	while(prompt[*i] && prompt[*i] != quote)
// 	{
// 		if (prompt[*i] == '$')
// 			res = 1;
// 		(*i)++;
// 	}
// 	if (prompt[*i] == quote)
// 		(*i)++;
// 	return (res);
// }

// int	which_quote(char *prompt, int *index)
// {
// 	while (prompt[*index])
// 	{
// 		if (prompt[*index] == '$')
// 		{
// 			(*index)++;
// 			return (DQ);
// 		}
// 		if (prompt[*index] == DQ && check_dollar_existence(prompt, index, DQ))
// 			return (DQ);
// 		if (prompt[*index] == SQ && check_dollar_existence(prompt, index, SQ))
// 			return (SQ);
// 		(*index)++;
// 	}
// 	return (DQ);
// }

// int	*fill_tab_quote(char *prompt, t_gmalloc **head)
// {
// 	int	i;
// 	int index;
// 	int dollars;
// 	int	*tab;

// 	i = 0;
// 	index = 0;
// 	dollars = count_dollars(prompt);
// 	tab = gb_malloc(sizeof(int) * dollars, head);
// 	while (i < dollars)
// 	{
// 		tab[i] = which_quote(prompt, &index);
// 		i++;	
// 	}
// 	return (tab);
// }

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
	// int		*quote_dollars;

	isolated = split_parts(prompt, &mini->gmalloc);
	// print_tab_char(isolated);
	// if (!isolated)
	// 	return (NULL);
	// quote_dollars = fill_tab_quote(prompt, &mini->gmalloc);
	// print_tab_int(quote_dollars);
	isolated = expend_each_var(isolated, mini->env, &mini->gmalloc, mini);
	if (!isolated)
		return (NULL);
	// gfree(quote_dollars, &mini->gmalloc);
	final = join_parts(isolated, &mini->gmalloc);
	gfree(isolated, &mini->gmalloc);
	// if (!final)
	// {
	// 	free_all(isolated);
	// 	return (NULL);
	// }
	return (final);
}
