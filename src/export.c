/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:21:24 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/27 20:13:24 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	dest = malloc(sizeof(char) * n + 1);
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

/*compte le nombre de string dans un char***/
int	nb_var(char **env)
{
	int	i;

	i = 0;
	while(env[i] != NULL)
		i++;
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
	res = malloc(sizeof(char *) * count);
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
		j++;
	}
	res[j] = NULL;
	return (res);
}

//on recupère la variable d'environnement et on y ajoute une nouvelle passé en argument
char	**ft_export(char **old_env, char *str)
{
	int		i;
	int		j;
	char	**new_env;
	char	*exp;
	char	**var_env_tab;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	new_env = malloc(sizeof(char *) * (nb_var(old_env) + 1));
	while (old_env[i] != NULL) //copier l'environnement dans 
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
	//regarde si il y a un '$' dans la string
	if (ft_strchr(str, '$'))//checker aussi si c'est entre simple quote ou pas
	{
		while (str[j] != '$')
			j++;
		new_env[i] = ft_strndup(str, j); //dup le debut de la string jusqu'au $
		var_env_tab = split_keep(str, '$'); //separé chaque $SOMETHING et les mettres dans un char**
		while (var_env_tab[k])
		{
			printf("%s\n", var_env_tab[k]);
			exp = expend(var_env_tab[k], old_env, false); //expend chaque variable d'environnement recupéré
			printf("%s\n", exp);
			if (exp) //si exp n'est pas null
			{
				new_env[i] = ft_strjoin(new_env[i], exp); //les joindrent a la suite du nouvel environnement
				free(exp);
			}
			k++;
		}
	}
	else //sinon juste ajouter la string au nouvel environnement
	{
		new_env[i] = ft_strdup(str);
		if (!new_env)
		{
			free_all(new_env);
			return (NULL);
		}
	}
	new_env[i + 1] = NULL;
	return (new_env);
}
