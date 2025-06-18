/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/18 11:49:53 by gaducurt         ###   ########.fr       */
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
	
// }

bool	ft_exec_cmd(t_cmd *cmd, char **env)
{
	char	**paths;
	int		nb_path;

	printf("exec_cmd\n");
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

int	ft_parsing(char *input, char **env, t_token *token)
{
	int		i;
	int		len_tab;
	int		nb_pipe;
	char	**prompt;
	// t_token	*token;
	t_cmd	*cmd;
	(void)env;

	i = 0;
	cmd = NULL;
	// syntaxe_error(input);
	len_tab = ft_count_word(input);
	// if	(ft_strchr(input, '$'))
	// 	prompt = handle_env_var(prompt);
	prompt = ft_multi_split(input);
	token = ft_tab_to_lst(prompt, len_tab);
	token = ft_handle_quote(token);
	
	// ft_print_lst(token);
	cmd = ft_init_cmd(token);
	printf("\n");
	ft_print_cmd(cmd);
	printf("\n");
	nb_pipe = ft_count_pipe(cmd);
	printf(CYAN"nb_pipe = %d\n"RESET, nb_pipe);
	if (nb_pipe > 0)
		pipex(cmd, env, nb_pipe, token); 



	
	/*-------------------useless---------------------------*/
	// ft_print_cmd(cmd);
	// cmd = ft_init_cmd(token);
	// cmd = malloc(sizeof(t_cmd));
	// cmd->args = prompt;
	// while (i < len_tab)
	// 	i++;
	// ft_check_lst(lst);
	// if (ft_is_pipe(lst))
	// 	pipex(lst);
	// else
		// ft_one_cmd(lst, cmd, env);
	return (1);
}
