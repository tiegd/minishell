/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:46:13 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/18 13:16:08 by jpiquet          ###   ########.fr       */
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

// int	which_quote(char *prompt, char **env)
// {
// 	int		i;
// 	int		index;
// 	// int		type;
// 	int 	start;
// 	char	**temp;
// 	(void)env;

// 	i = 0;
// 	start = 0;
// 	index = 0;
// 	temp = malloc(sizeof(char *) * (count_part_to_join(prompt) + 2));
// 	if (!temp)
// 		return (NULL);
// 	while (prompt[i])
// 	{
// 		while (prompt[i] != '$')
// 			i++;
// 		temp[index] = ft_substr(prompt, start, i);
// 		while(prompt[i])
// 		{
// 			while (prompt[i] != '$')
// 				i++;
// 			temp = ft_substr(prompt, start, i);
// 			start = i;
// 			i++;
// 			while (prompt[i] && exp_isalnum(prompt[i]))
// 				i++;
// 			exp = ft_substr(prompt, start, i);
// 			exp = expend(exp, env);
// 			temp = ft_strjoin_custom(temp, exp);
// 		}
// 	}
// 	return 0;
	
// }



void	print_tab_char(char **tab)
{
	int	i;
	
	i = 0;
	while (tab[i])
	{
		printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
}

char	**expend_each_var(char **isolated, char **env, int *quote_dollars)
{
	int	i;
	int index;

	i = 0;
	index = 0;
	while(isolated[i])
	{
		if (strchr(isolated[i], '$') && quote_dollars[index] == DQ)
		{
			isolated[i] = expend(isolated[i], env);
			index++;
		}
		i++;
	}
	return (isolated);
}

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
	return (res);
}

int	which_quote(char *prompt)
{
	static int	i;

	while (prompt[i])
	{
		if (prompt[i] == '$')
		{
			i++;
			return (DQ);
		}
		if (prompt[i] == DQ && check_dollar_existence(prompt, &i, DQ))
			return (DQ);
		if (prompt[i] == SQ && check_dollar_existence(prompt, &i, SQ))
			return (SQ);
		i++;
	}
	return (DQ);
}

int	*fill_tab_quote(char *prompt)
{
	int	i;
	int dollars;
	int	*tab;

	i = 0;
	dollars = count_dollars(prompt);
	tab = malloc(sizeof(int) * dollars);
	while (i < dollars)
	{
		tab[i] = which_quote(prompt);
		i++;	
	}
	return (tab);
}

char	*handle_env_var(char *prompt, char **env)
{
	char 	**isolated;
	char	**final;
	int		*quote_dollars;

	isolated = split_parts(prompt);
	if (!isolated)
		return (NULL);
	quote_dollars = fill_tab_quote(prompt);
	free(prompt);
	final = expend_each_var(isolated, env, quote_dollars);
	print_tab_char(final);

	return (NULL);
}
