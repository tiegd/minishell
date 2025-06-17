/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:18:55 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/17 13:02:42 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*isalnum où le '_' est autorisé*/
int	exp_isalnum(int c) 
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	else
		return (0);
}

// /*compare les strings jusqu'au caractère passé en paramètre*/
// int		strcmp_until_char(char *s1, char *s2, char c)
// {
// 	int	i;
	
// 	i = 0;
// 	if (!s1 || !s2)
// 		return (0);
// 	while (s1[i] && s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return (0);
// 		i++;
// 	}
// 	if (s1[i - 1] - s2[i - 1] == 0 && s2[i] == c)
// 		return (1);
// 	return (0);
// }

// /*récupère le resultat d'une variable d'environnement*/
// char	*env_result(char *env, bool malloc_error)
// {
// 	int	i;
// 	char *res;

// 	i = 0;
// 	// res = NULL;
// 	while (env[i] && env[i] != '=')
// 	{
// 		i++;
// 	}
// 	if (env[i] && env[i] == '=')
// 		i++;
// 	env += i;
// 	res = ft_strdup(env);
// 	if (!res)
// 	{
// 		malloc_error = true;
// 		return (NULL);
// 	}
// 	return (res);
// }

// //extrait la variable d'environnement si elle existe, sinon renvoie NULL.
// char	*extract_env(char *temp, char **env, bool malloc_error)
// {
// 	int	i;
// 	int	temp_len;
// 	char *extract;

// 	i = 0;
// 	temp_len = ft_strlen(temp);
// 	while (env[i] != NULL)
// 	{
// 		if (strcmp_until_char(temp, env[i], '='))
// 		{
// 			extract = env_result(env[i], malloc_error);
// 			if (!extract)
// 			{
// 				malloc_error = true;
// 				return (NULL);
// 			}
// 			return (extract);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

/*fonction permettant de transforner un $SOMETHING en resultat de sa variable d'environnement, 
renvoie un char* ou NULL si la variable n'est pas trouvé.*/
char	*expend(char *arg, char **env) //bool malloc_error)
{
	int	i;
	int	start;
	int len;
	char *temp;
	char *expend;
	(void)env;

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
	if (!temp)
	{
		// malloc_error = true;
		return (NULL);
	}
	expend = getenv(temp); //extract_env(temp, env, malloc_error);
	free(temp);
	free(arg);
	return (expend);
}
