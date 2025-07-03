/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/03 09:57:03 by jpiquet          ###   ########.fr       */
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

// Check if the cmd exist with access().
char	*ft_is_bin(char **paths, int nb_path)
{
	int		i;

	i = 0;
	while (i <= nb_path)
	{
		if (access(paths[i], F_OK) == 0)
			return (paths[i]);
		i++;
	}
	return (NULL);
}

// Check if the firt word is a cmd or anything right.

// bool	ft_first_word(t_token *lst)
// {
// 	if (ft_strlen(lst->content) == 1 && lst->content[0] == '<')
// 		return (true);
// 	else if (ft_strlen(lst->content) == 2 && lst->content[0] == '<' && lst->content[1] == '<')
// 		return (true);
// 	else if (ft_is_builtin(lst->content))
// 	{
// 		printf(CYAN"Builtin = %s\n"RESET, lst->content);
// 		// ft_exec_builtin();
// 		return (true);
// 	}
// 	else
// 		return (false);
// }

// Run the cmd if it's a builtin.

int	ft_exec_builtin(char **args)
{
	(void)args;
	return (0);
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

bool	ft_exec_cmd(t_cmd *cmd, char **env)
{
	char	**paths;
	int		nb_path;

	nb_path = ft_count_path(getenv("PATH"));
	// printf(GREEN"nb_path = %d\n"RESET, nb_path);
	paths = ft_split(getenv("PATH"), ':');
	// ft_print_tab(paths, nb_path);
	// printf(RED"-------------------------------------------------------\n"RESET);
	paths = ft_add_cmd(paths, nb_path, cmd);
	// ft_print_tab(paths, nb_path);
	if (ft_is_bin(paths, nb_path))
	{
		cmd->pathname = ft_is_bin(paths, nb_path);
		// printf(RED"Right path = %s\n"RESET, cmd->pathname);
		execve(cmd->pathname, cmd->args, env);
	}
	else if (is_builtin(cmd->args[0]))
	{
		if (ft_exec_builtin(cmd->args))
			exit(0);
	}
	return (false);
}

int	ft_parsing(char *input, char **env)
{
	int		len_tab;
	char	**prompt;
	t_token	*token;
	t_cmd	*cmd;
	t_data	data;

	cmd = NULL;
	syntaxe_error(input);
	// len_tab = ft_count_word(input);
	if	(ft_strchr(input, '$'))
		input = handle_env_var(input, env);
	// printf("apres handle var = %s\n", input);
	prompt = ft_multi_split(input);
	len_tab = count_tab(prompt);
	token = ft_tab_to_lst(prompt, len_tab);
	token = ft_handle_quote(token);
	// ft_print_lst(token);
	cmd = ft_init_cmd(token);
	// ft_print_redir(cmd->infiles);
	// ft_print_redir(cmd->outfiles);
	// ft_print_cmd(cmd);

	return (0);
}
