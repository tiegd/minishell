/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:21:24 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/30 13:31:07 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_custom(char *s1, char *s2)
{
	int		tlen;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	tlen = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * tlen + 1);
	if (str == 0)
		return (NULL);
	while (s1[j] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

/*duplique une string jusqu'à n caractère*/
char	*ft_strndup(const char *s, int n)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(s);
	if (n <= 0)
		return (NULL);
	dest = malloc(sizeof(char) * (n + 1));
	if (dest == 0)
		return (0);
	while (s[i] != '\0' && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*compte le nombre de string dans un char** */
int	nb_var(char **env)
{
	int	i;

	i = 0;
	while(env[i] != NULL)
	{
		// printf("%s\n", env[i]);
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

/*avance jusqu'au séparateur et renvoie un char** de chaque spéparateur + la string qui suit*/
char	**split_keep(char *str, char c)
{
	int 	i;
	int		j;
	int		index;
	int		count;
	int		start;
	char	**res;
	
	i = 0;
	j = 0;
	count = char_nb(str, c);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		index = 0;
		while(str[i] && str[i] != c)
		{
			i++;
		}
		start = i;
		while (str[i + 1] && str[i + 1] != c)
		{
			i++;
		}
		i += 1;
		res[j] = malloc(sizeof(char) * (i - start + 1));
		if (!res)
		{
			free_all(res);
			return (NULL);
		}
		while (start < i)
		{
			res[j][index] = str[start];
			index++;
			start++;
		}
		res[j][index] = '\0';
		j++;
	}
	res[j] = NULL;
	return (res);
}

/*duplique la variable d'environnement passé en paramètre et renvoie un char** ou NULL si il y a une erreur */
char	**envdup(char **old_env)
{
	int		i;
	int		env_len;
	char 	**new_env;

	i = 0;
	env_len = nb_var(old_env);
	new_env = malloc(sizeof(char *) * (env_len + 2));
	while (old_env[i] != NULL) //copier l'environnement dans new env et retourner le tableau de string
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (!new_env)
		{
			free_all(old_env);
			free_all(new_env);
			return (NULL);
		}
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
	if (s1[i] - s2[i] == 0)
		return (1);
	return (0);
}

//on recupère la variable d'environnement et on y ajoute une nouvelle passé en argument
char	**ft_export(char **old_env, char *str)
{
	int		i;
	int		j;
	int		k;
	char	**new_env;
	char	*exp;
	char	**var_env_tab;
	char	*new_variable;

	j = 0;
	k = 0;
	new_env = envdup(old_env); //duplique lénvironnement dans un nouveau tableau de string
	if (!new_env)
		return (NULL);
	new_variable = ft_strdup(str); //duplique la variable d'environnement qu'on va rajouter à l'environnement
	if (!new_variable)
		return (NULL);
	//regarde si il y a un '$' dans la string
	if (ft_strchr(str, '$'))//checker aussi si c'est entre simple quote ou pas
	{
		free(new_variable);
		while (str[j] != '$')
			j++;
		new_variable = ft_strndup(str, j); //dup le debut de la string jusqu'au $
		// printf("new_variable = %s\n", new_variable);
		var_env_tab = split_keep(str, '$'); //separé chaque $SOMETHING et les mettres dans un char**
		while (var_env_tab[k] != NULL)
		{
			// printf("%s\n", var_env_tab[k]);
			exp = expend(var_env_tab[k], old_env, false); //expend chaque variable d'environnement recupéré.
			if (exp) //si exp n'est pas null
			{
				new_variable = ft_strjoin_custom(new_variable, exp); //les joindrent a la suite de la nouvelle variable.
				// free(exp);
			}
			k++;
		}
		free_all(var_env_tab);
	}
	//on regarde si la variable existe déjà et si oui on la remplace par la nouvelle
	i = 0;
	while (new_env[i])
	{
		//si elle existe on renvoit le nouvelle environnement avec la variable remplacé
		if (env_var_cmp(new_env[i], new_variable))
		{
			new_env[i] = ft_strdup(new_variable);
			free(new_variable);
			return (new_env);
		}
		i++;
	}
	//sinon juste ajouter la string au nouvel environnement
	// printf("ERROR\n");
	i = nb_var(old_env);
	new_env[i] = ft_strdup(new_variable);
	if (!new_env)
	{
		free_all(new_env);
		return (NULL);
	}
	new_env[i + 1] = NULL;
	free(new_variable);
	return (new_env);
}

/*d'abord expend si il y a des $ dan la variable d'environnement et ensuite checker si elle existe deja ou si on doit juste l'ajouter a l'environnement*/

char	**loop_export(char **env, char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		env = ft_export(env, args[i]);
		i++;
	}
	return (env);
}
