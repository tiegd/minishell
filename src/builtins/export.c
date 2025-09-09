/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:21:24 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 08:23:44 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*compte le nombre de string dans un char** */

int	nb_var(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		i++;
	}
	return (i);
}

/*duplique la variable d'environnement passé en paramètre 
et renvoie un char** ou NULL si il y a une erreur */

char	**envdup(char **old_env, t_gmalloc **head)
{
	int		i;
	int		env_len;
	char	**new_env;

	i = 0;
	env_len = nb_var(old_env);
	new_env = gb_malloc(sizeof(char *) * (env_len + 2), head);
	while (old_env[i] != NULL)
	{
		new_env[i] = gb_strdup(old_env[i], head);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

/*on recupère la variable d'environnement 
et on y ajoute une nouvelle passé en argument
duplique l'environnement dans un nouveau tableau de string
on regarde si la variable existe déjà 
et si oui on la remplace par la nouvelle
si elle existe on renvoit le nouvelle environnement avec la variable remplacé
sinon juste ajouter la string au nouvel environnement*/

char	**ft_export(char **env, char *new_var, t_mini *mini, t_gmalloc **head)
{
	int		i;
	char	**new_env;

	if (!is_valid_identifier(new_var, mini))
		return (env);
	new_env = envdup(env, head);
	i = 0;
	while (new_env[i])
	{
		if (handle_same_var(new_var, new_env, i, head))
			return (new_env);
		i++;
	}
	i = nb_var(env);
	new_env[i] = gb_strdup(new_var, head);
	new_env[i + 1] = NULL;
	gfree(new_var, head);
	return (new_env);
}

/*d'abord expend si il y a des $ dan la variable d'environnement 
et ensuite checker si elle existe deja 
ou si on doit juste l'ajouter a l'environnement*/

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
