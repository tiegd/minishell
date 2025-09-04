/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:18:55 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/04 17:27:58 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*compare les strings jusqu'au caractère passé en paramètre*/
int		strcmp_until_char(char *s1, char *s2, char c)
{
	int	i;
	
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i - 1] - s2[i - 1] == 0 && s2[i] == c) 
		return (1);
	return (0);
}

char	*add_double_quote(char *res, t_gmalloc **head)
{
	int	i;
	int	len;
	int	j;
	char *temp;

	i = 0;
	j = 0;
	len = ft_strlen(res);
	temp = gb_malloc((len + 3) * sizeof(char), head);
	temp[i] = '"';
	i++;
	while (res[j])
		temp[i++] = res[j++];
	temp[i++] = '"';
	temp[i] = '\0';
	return (temp);
}

int	has_special(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_special(str[i]))
			return (1);
		i++;
	}
	return (0);
}

/*récupère le resultat d'une variable d'environnement*/
char	*env_result(char *env, t_gmalloc **head)
{
	int	i;
	char *res;

	i = 0;
	// res = NULL;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] && env[i] == '=')
		i++;
	env += i;
	res = gb_strdup(env, head);
	if (has_special(res))
		res = add_double_quote(res, head);
	return (res);
}

// For count the number of char for ft_itoa().
static int	count_size(int n)
{
	int i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*gb_itoa(int nb, t_gmalloc **head)
{
	char	*dest;
	int		count;
	int		n;
	int		i;

	n = nb;
	count = count_size(n);
	i = 0;
	if (n < 0 || count == 0)
		count++;
	dest = gb_malloc(((count + 1) * sizeof(char)), head);
	if (n < 0)
	{
		n *= -1;
		dest[0] = '-';
		i++;
	}
	dest[count] = '\0';
	while (count > i)
	{
		count--;
		dest[count] = (n % 10) + '0';
		n /= 10;
	}
	return (dest);
}

//extrait la variable d'environnement si elle existe, sinon renvoie NULL.
char	*extract_env(char *temp, char **env, t_gmalloc **head, t_mini *mini)
{
	int	i;
	char *extract;
	(void)mini;

	i = 0;
	while (env[i] != NULL)
	{
		if (strcmp_until_char(temp, env[i], '='))
		{
			extract = env_result(env[i], head);
			return (extract);
		}
		i++;
	}
	return (NULL);
}

/*fonction permettant de transforner un $SOMETHING en resultat de sa variable d'environnement, 
renvoie un char* ou NULL si la variable n'est pas trouvé.*/
// char	*expend(char *arg, char **env)
// {
// 	int	i;
// 	int	start;
// 	int len;
// 	char *temp;
// 	char *expend;
// 	(void)env;

// 	i = 0;
// 	while (arg[i] != '\0' && arg[i] != '$')
// 		i++;
// 	start = i + 1;
// 	if (arg[i] == '$')
// 		i++;
// 	while (arg[i] && exp_isalnum(arg[i]))
// 		i++;
// 	len = i - start;
// 	temp = ft_substr(arg, start, len);
// 	if (!temp)
// 		return (NULL);
// 	expend = getenv(temp);
// 	free(temp);
// 	free(arg);
// 	return (expend);
// }

// char	*expend(char *arg, char **env, t_gmalloc **head)
// {
// 	int	i;
// 	char *expend;
// 	// int	start;
// 	// int len;
// 	// char *temp;

// 	i = 0;
// 	while (*arg != '\0' && *arg != '$')
// 		arg++;
// 	if (*arg == '$')
// 		arg++;
// 	// if (!temp)
// 	// 	return (NULL);
// 	expend = getenv(arg);
// 	if (!expend)
// 	{
// 		expend = gb_malloc(sizeof(char) + 1, head);
// 		expend[0] = '\0';
// 	}
// 	// free(temp);
// 	// free(arg);
// 	return (expend);
// }

char	*expend_exit_status(char *arg, t_gmalloc **head, t_mini *mini)
{
	char	*res;
	char	*exit_status;
	int		total_len;
	int		i;
	int		j;
	
	i = 0;
	j = 1;
	exit_status = gb_itoa(mini->exit_status, head);
	total_len = ft_strlen(arg) + ft_strlen(exit_status) - 1;
	res = gb_malloc((total_len + 1) * sizeof(char), head);
	while (exit_status[i])
	{
		res[i] = exit_status[i];
		i++;
	}
	while (arg[j])
		res[i++] = arg[j++];
	res[i] = '\0';
	return (res);
}

char	*expend(char *arg, char **env, t_gmalloc **head, t_mini *mini)
{
	char *expend;

	while (*arg != '\0' && *arg != '$')
		arg++;
	if (*arg == '$')
		arg++;
	if (!*arg)
		return (NULL);
	if (*arg == '?')
	{
		expend = expend_exit_status(arg, head, mini);
		gfree(arg, head);
		return (expend);
	}
	expend = extract_env(arg, env, head, mini);
	if (!expend)
	{
		expend = gb_malloc(sizeof(char) + 2, head);
		expend[0] = DQ;
		expend[1] = DQ;
		expend[2] = '\0';
	}
	gfree(arg, head);
	return (expend);
}
