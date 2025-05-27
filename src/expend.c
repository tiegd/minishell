/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:18:55 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/27 17:02:51 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_isalnum(int c) //is al num ou le '_' est autorisé
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	else
		return (0);
}

int		strcmp_until_char(char *s1, char *s2, char c)
{
	int	i;
	
	i = 0;
	printf("s1 = %s\n", s1); 
	printf("s2 = %s\n", s2);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	printf("ERROR\n");
	if (s1[i] - s2[i] == 0 && s2[i + 1] == '=')
		return (1);
	printf("APRES COMPARAISON\n");
	return (0);
}

char	*env_result(char *env, bool malloc_error)
{
	int	i;
	char *res;

	i = 0;
	while (env[i] && env[i] != '=')
	{
		i++;
	}
	if (env[i] && env[i] == '=')
		i++;
	env += i;
	printf("%s\n", env);
	res = ft_strdup(env);
	if (!res)
	{
		malloc_error = true;
		return (NULL);
	}
	printf("res = %s\n", res);
	return (res);
}

char	*extract_env(char *temp, char **env, bool malloc_error)
{
	int	i;
	int	temp_len;
	char *extract;

	i = 0;
	temp_len = ft_strlen(temp);
	while (env[i] != NULL)
	{
		if (strcmp_until_char(temp, env[i], '='))
		{
			extract = env_result(env[i], malloc_error);
			if (!extract)
			{
				malloc_error = true;
				return (NULL);
			}
			return (extract);
		}
		i++;
	}
	return (NULL);
}

char	*expend(char *arg, char **env, bool malloc_error)
{
	int	i;
	int	start;
	int len;
	char *temp;
	char *expend;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '$')
		i++;
	start = i + 1;
	if (arg[i] == '$')
		i++;
	while (arg[i] && exp_isalnum(arg[i]))
	{
		i++;
	}
	len = i - start;
	temp = ft_substr(arg, start, len);
	// printf("temp = %s\n", temp);
	if (!temp)
	{
		malloc_error = true;
		return (NULL);
	}
	// printf("%s\n", temp);
	expend = extract_env(temp, env, malloc_error);
	return (expend);
}

