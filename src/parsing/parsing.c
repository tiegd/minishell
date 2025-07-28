/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/28 13:04:44 by gaducurt         ###   ########.fr       */
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
	if (args[0] == '/' && args[1] == 'b' && args[2] == 'i' && args[3] == 'n' && args[4] == '/')
		i = 5;
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
	// free_double_tab(paths, nb_path,);
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
	if (!path)
		return (i);
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

int	prompt_is_empty(char *input)
{
	int	i;
	
	i = 0;
	while (input[i])
	{
		if (!is_ws(input[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_parsing(char *input, t_mini *mini)
{
	int		len_tab;
	int		nb_pipe;
	char	**prompt;
	// int 	fd_here_doc;

	mini->cmd = NULL;
	if (prompt_is_empty(input))
		return (0);
	if (syntax_error(input))
		return (str_return("minishell : syntax error\n", 2, mini));
	if	(ft_strchr(input, '$'))
		input = handle_env_var(input, mini);
	prompt = ft_multi_split(input, &mini->gmalloc);
	// print_tab_char(prompt);
	// printf("ERROR\n");
	len_tab = count_tab(prompt);
	mini->token = ft_tab_to_lst(prompt, len_tab, &mini->gmalloc);
	mini->token = ft_handle_quote(mini->token);
	mini->cmd = ft_init_cmd(mini->token, &mini->gmalloc);
	if (mini->cmd->infiles && mini->cmd->infiles->type == HERE_DOC)
	{
		// printf("ENTRER\n");
		mini->cmd->fd_infile = here_doc(mini->cmd->infiles->filename, &mini->gmalloc);
	}
	// ft_print_redir(mini->cmd->infiles);
	// ft_print_redir(mini->cmd->outfiles);
	// ft_print_cmd(mini->cmd);
	nb_pipe = ft_count_pipe(&mini->token);
	if (nb_pipe > 0)
	{
		// pipex(mini->cmd, mini->env, nb_pipe, &mini->gmalloc);
		pipex(mini->cmd, mini, nb_pipe, &mini->gmalloc);
	}
	else
		ft_one_cmd(mini->cmd, mini, &mini->gmalloc);
	return (0);
}
