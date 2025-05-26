/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:18:55 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/26 11:06:59 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		charcmp(char *s1, char *s2, char s2_set)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] && s2[i] && s2[i] != s2_set)
// 	{
// 		if (s1[i] != s2[i])
// 			return (0);
// 		i++;
// 	}
// 	if ((s1[i] == '\0' || s1[i] == 39) && s2[i] == s2_set)
// 		return (1);
// 	return (0);
// }

// void	print_envariable(char *str)
// {
// 		int	i;

// 		i = 0;
// 		while (str[i] != '\0' && str[i] != '=')
// 			i++;
// 		if (str[i] != '\0' && str[i] == '=')
// 			i++;
// 		while(str[i])
// 			write(1, &str[i], 1);
// }

// void	is_env_var(char	*str, char **env)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	*str++;
// 	while (env[i])
// 	{
// 		if (charcmp(str, env[i], '='))
// 		{
// 			print_envariable(env[i]);
// 			break;
// 		}
// 		i++;
// 	}
// }

// char	*

// char	*extract_env()

// char	*expend(char *arg, char **env, bool malloc_error)
// {
// 	int	i;
// 	int	start;
// 	int len;
// 	char *temp;
// 	char *expend;
// 	(void)env;

// 	i = 0;
// 	start = 0;
// 	printf("%s\n", arg);
// 	// if (!there_is_var_env(arg))
// 	// {
// 	// 	expend = malloc(sizeof(char));
// 	// 	expend[0] = '\0';
// 	// 	return (expend);
// 	// }
// 	while (arg[i] != '\0' && arg[i] != '$')
// 		i++;
// 	start = i + 1;
// 	if (arg[i] == '$')
// 		i++;
// 	while (arg[i] && ft_isalnum(arg[i]))
// 	{
// 		printf("%c\n", arg[i]);
// 		i++;
// 	}
// 	len = i - start;
// 	temp = ft_substr(arg, start, len);
// 	if (!temp)
// 	{
// 		malloc_error = true;
// 		return (NULL);
// 	}
// 	expend = extract_env(temp, env);
// 	return (expend);
// }

