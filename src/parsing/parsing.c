/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/03 14:42:25 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "minishell.h"

bool	ft_is_pipe(t_token *lst)
{
	t_token	*tmp;
	int		i;

	tmp = lst;
	while (tmp->next)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '|')
				return (true);
			i++;
		}
		tmp = tmp->next;
	}
	return (false);
}

int	ft_count_path(char *paths)
{
	int	nb_path;
	int	i;

	nb_path = 0;
	i = 0;
	while (paths[i])
	{
		while (paths[i] && paths[i] == ':')
			i++;
		if (paths[i] && paths[i] != ':')
			nb_path++;
		while (paths[i] && paths[i] != ':')
			i++;
	}
	return (nb_path);
}

char	*ft_add_suf(int j, char *str, char *args)
{
	int	i;

	i = 0;
	str[j] = '/';
	j++;
	while (args[i])
	{
		str[j] = args[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

// Add the cmd at the end of each path.

char	**ft_add_cmd(char **paths, int nb_path, t_cmd *cmd)
{
	char	**new_tab;
	int		size_cmd;
	int		size_line;
	int		i;
	int		j;

	i = 0;
	size_cmd = (int)ft_strlen(cmd->args[0]) + 1;
	new_tab = malloc((nb_path + 1) * sizeof(char *));
	while (i < nb_path)
	{
		j = 0;
		size_line = (int)ft_strlen(paths[i]) + size_cmd + 1;
		new_tab[i] = malloc(size_line * sizeof(char));
		while (paths[i][j])
		{
			new_tab[i][j] = paths[i][j];
			j++;
		}
		new_tab[i] = ft_add_suf(j, new_tab[i], cmd->args[0]);
		i++;
	}
	free_double_tab(paths, nb_path);
	return (new_tab);
}

char	*ft_path_line(char **env)
{
	int		i;
	int		j;
	int		len;
	char	*path;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			j = 0;
			len = ft_strlen(env[i]) - 5;
			path = malloc((len + 1) * sizeof(char));
			while (env[i][j + 5])
			{
				path[j] = env[i][j + 5];
				j++;
			}
			path[j] = '\0';
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	ft_nb_path(char **path)
{
	int	i;
	i = 0;
	while (path[i] != NULL)
		i++;
	return (i);
}

// void	ft_multi_cmd(lst)
// {
// 	int	nb_path;
// 	int	i;

// 	nb_path = 0;
// 	i = 0;
// 	while (paths[i])
// 	{
// 		while (paths[i] && paths[i] == ':')
// 			i++;
// 		if (paths[i] && paths[i] != ':')
// 			nb_path++;
// 		while (paths[i] && paths[i] != ':')
// 			i++;
// 	}
// 	return (nb_path);
// }

// char	**ft_clean_path(char **double_tab, int nb_path)
// {
// 	int	i;

// 	i = 0;
// 	while (i < nb_path)
// 	{
// 		free(double_tab[i]);
// 		i++;
// 	}
// 	free(double_tab);
// 	return (NULL);
// }

// char	*ft_add_suf(t_token *lst, int j, char *str)
// {
// 	int	k;

// 	k = 0;
// 	str[j] = '/';
// 	j++;
// 	while (lst->content[k])
// 	{
// 		str[j] = lst->content[k];
// 		k++;
// 		j++;
// 	}
// 	str[j] = '\0';
// 	return (str);
// }

// // Add the cmd at the end of each path.
// char	**ft_add_cmd(t_token *lst, char **paths, int nb_path)
// {
// 	char	**new_tab;
// 	int		size_cmd;
// 	int		size_line;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	size_cmd = (int)ft_strlen(lst->content) + 1;
// 	new_tab = malloc((nb_path + 1) * sizeof(char *));
// 	while (i < nb_path)
// 	{
// 		j = 0;
// 		size_line = (int)ft_strlen(paths[i]) + size_cmd + 1;
// 		new_tab[i] = malloc(size_line * sizeof(char));
// 		while (paths[i][j])
// 		{
// 			new_tab[i][j] = paths[i][j];
// 			j++;
// 		}
// 		new_tab[i] = ft_add_suf(lst, j, new_tab[i]);
// 		i++;
// 	}
// 	ft_clean_path(paths, nb_path);
// 	return (new_tab);
// }

// // Check if the cmd exist with access().
// char	*ft_is_bin(char **paths, int nb_path)
// {
// 	int		i;

// 	i = 0;
// 	while (i <= nb_path)
// 	{
// 		if (access(paths[i], F_OK) == 0)
// 			return (paths[i]);
// 		i++;
// 	}
// 	return (NULL);
// }

int	ft_parsing(char *input, char **env)
{
	int		len_tab;
	int		nb_pipe;
	char	**prompt;
	t_token	*token;
	t_cmd	*cmd;
	// t_data	data;

	cmd = NULL;
	// syntaxe_error(input);
	// len_tab = ft_count_word(input);
	if	(ft_strchr(input, '$'))
		input = handle_env_var(input, env);
	// printf("apres handle var = %s\n", input);
	prompt = ft_multi_split(input);
	len_tab = count_tab(prompt);
	token = ft_tab_to_lst(prompt, len_tab);
	token = ft_handle_quote(token);
	cmd = ft_init_cmd(token);
	ft_print_cmd(cmd);
	nb_pipe = ft_count_pipe(cmd);
	if (nb_pipe > 0)
		pipex(cmd, env, nb_pipe); 
	else
		ft_one_cmd(cmd, env);
	return (0);
}
