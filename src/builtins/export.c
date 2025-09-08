/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerzone <amerzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:21:24 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/05 16:00:52 by amerzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*compte le nombre de string dans un char** */
int	nb_var(char **env)
{
	int	i;

	i = 0;
	while(env[i] != NULL)
	{
		i++;
	}
	return (i);
}

/*compte le nombre de séparateur dans la string*/
int		char_nb(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

// /*avance jusqu'au séparateur et renvoie un char** 
// de chaque spéparateur + la string qui suit*/
// char	**split_keep(char *str, char c)
// {
// 	int 	i;
// 	int		j;
// 	int		index;
// 	int		count;
// 	int		start;
// 	char	**res;
	
// 	i = 0;
// 	j = 0;
// 	count = char_nb(str, c);
// 	res = malloc(sizeof(char *) * (count + 1));
// 	if (!res)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		index = 0;
// 		while(str[i] && str[i] != c)
// 		{
// 			i++;
// 		}
// 		start = i;
// 		while (str[i + 1] && str[i + 1] != c)
// 		{
// 			i++;
// 		}
// 		i += 1;
// 		res[j] = malloc(sizeof(char) * (i - start + 1));
// 		if (!res)
// 		{
// 			free_all(res);
// 			return (NULL);
// 		}
// 		while (start < i)
// 		{
// 			res[j][index] = str[start];
// 			index++;
// 			start++;
// 		}
// 		res[j][index] = '\0';
// 		j++;
// 	}
// 	res[j] = NULL;
// 	return (res);
// }

/*duplique la variable d'environnement passé en paramètre et renvoie un char** ou NULL si il y a une erreur */

char	**envdup(char **old_env, t_gmalloc **head)
{
	int		i;
	int		env_len;
	char 	**new_env;

	i = 0;
	env_len = nb_var(old_env);
	new_env = gb_malloc(sizeof(char *) * (env_len + 2), head);
	while (old_env[i] != NULL) //copier l'environnement dans new env et retourner le tableau de string
	{
		new_env[i] = gb_strdup(old_env[i], head);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

//compare le nom de 2 variable d'environnement

int		env_var_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i - 1] - s2[i - 1] == 0 && s1[i] - s2[i] == 0)
		return (1);
	else if (s1[i - 1] - s2[i - 1] == 0 && s1[i] == '\0' && s2[i] == '=')
		return (2);
	return (0);
}

int	is_valid_identifier(char *variable, t_mini *mini)
{
	int	i;

	i = 0;
	if (ft_isdigit(variable[0]) || !exp_isalnum(variable[0]))
	{
		mini->exit_status = 1;
		print_not_valid_identifier(variable);
		return (0);
	}
	while (variable[i] && variable[i] != '=')
	{
		if(!exp_isalnum(variable[i]))
		{
			mini->exit_status = 1;
			print_not_valid_identifier(variable);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_empty_var(char *variable)
{
	int	i;

	i = 0;
	while (variable[i])
	{
		if (variable[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	replace_same_var(char *new_variable, char **new_env, int i, t_gmalloc **head)
{
	if (!is_empty_var(new_variable))
	{
		gfree(new_env[i], head);
		new_env[i] = gb_strdup(new_variable, head);
	}
	gfree(new_variable, head);
}

void	handle_same_var(char *new_variable, char **new_env, int i, t_gmalloc **head)
{
	
}
/*on recupère la variable d'environnement et on y ajoute une nouvelle passé en argument
duplique l'environnement dans un nouveau tableau de string
on regarde si la variable existe déjà et si oui on la remplace par la nouvelle
si elle existe on renvoit le nouvelle environnement avec la variable remplacé
sinon juste ajouter la string au nouvel environnement*/

char	**ft_export(char **old_env, char *new_variable, t_mini *mini, t_gmalloc **head)
{
	int		i;
	char	**new_env;

	if (!is_valid_identifier(new_variable, mini))
		return (old_env);
	new_env = envdup(old_env, head);
	i = 0;
	while (new_env[i])
	{
		if (env_var_cmp(new_env[i], new_variable) == 1 
		|| env_var_cmp(new_env[i], new_variable) == 2)
		{
			replace_same_var(new_variable, new_env, i, head);
			return (new_env);
		}
		else if (env_var_cmp(new_variable, new_env[i]) == 2)
		{
			gfree(new_variable, head);
			return (new_env);
		}
		i++;
	}
	i = nb_var(old_env);
	new_env[i] = gb_strdup(new_variable, head);
	new_env[i + 1] = NULL;
	gfree(new_variable, head);
	return (new_env);
}

/*d'abord expend si il y a des $ dan la variable d'environnement 
et ensuite checker si elle existe deja ou si on doit juste l'ajouter a l'environnement*/
char	**loop_export(char **env, char **args, t_mini *mini, t_gmalloc **head)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		env = ft_export(env, args[i], mini, head);
		i++;
	}
	mini->exit_status = 0;
	return (env);
}


// char	**ft_export(char **old_env, char *new_variable, t_mini *mini, t_gmalloc **head)
// {
// 	int		i;
// 	char	**new_env;

// 	if (!is_valid_identifier(new_variable, mini)) // || is_empty_var(new_variable))
// 		return (old_env);
// 	new_env = envdup(old_env, head);
// 	i = 0;
// 	while (new_env[i])
// 	{
// 		if (env_var_cmp(new_env[i], new_variable) == 1)
// 		{
// 			if (!is_empty_var(new_variable))
// 			{
// 				gfree(new_env[i], head);
// 				new_env[i] = gb_strdup(new_variable, head);
// 			}
// 			gfree(new_variable, head);
// 			return (new_env);
// 		}
// 		else if (env_var_cmp(new_env[i], new_variable) == 2)
// 		{
// 			if (!is_empty_var(new_variable))
// 			{
// 				gfree(new_env[i], head);
// 				new_env[i] = gb_strdup(new_variable, head);
// 			}
// 			gfree(new_variable, head);
// 			return (new_env);
// 		}
// 		else if (env_var_cmp(new_variable, new_env[i]) == 2)
// 		{
// 			gfree(new_variable, head);
// 			return (new_env);
// 		}
// 		i++;
// 	}
// 	i = nb_var(old_env);
// 	new_env[i] = gb_strdup(new_variable, head);
// 	new_env[i + 1] = NULL;
// 	gfree(new_variable, head);
// 	return (new_env);
// }