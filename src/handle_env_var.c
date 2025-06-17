/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:46:13 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/17 14:48:34 by jpiquet          ###   ########.fr       */
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
	printf("count : %d\n", count);
	return (count);
}

char	**which_quote(char *prompt, char **env)
{
	int		i;
	int		index;
	// int		type;
	int 	start;
	char	**temp;
	(void)env;

	i = 0;
	index = 0;
	temp = malloc(sizeof(char *) * (count_part_to_join(prompt) + 2));
	if (!temp)
		return (NULL);
	while (prompt[i])
	{
		start = i;
		while (prompt[i] && prompt[i] != '$')
			i++;
		temp[index] = ft_substr(prompt, start, i - start);
		start = i;
		index++;
		if (prompt[i] == '$')
		{
			i++;
			while(prompt[i] && exp_isalnum(prompt[i]))
				i++;
			temp[index] = ft_substr(prompt, start, i - start);
			index++;
		}
		if (prompt[i] == '\0')
			break;
		i++;
	}
	return (temp);
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

char	*handle_env_var(char *prompt, char **env)
{
	// int		i;
	// char	*var_res;
	// char	*final;
	// int		total_len;
	char **final;
	
	final = which_quote(prompt, env);
	print_tab_char(final);
	exit(1);
	return (NULL);
}