/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/18 09:23:19 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>


// // Check if the first word is a builtin commande.
// int	ft_is_builtin(char *input, int end_word)
// {
// 	int	i;

// 	i = 0;
// 	while (i < end_word)
// 	{
// 		(void)input;
// 		// checker si ca correspond à un nom de fonction
// 		i++;
// 	}
// 	return (1);
// }

int	ft_str_digit(char *input, int end_word)
{
	int	i;

	i = 0;
	while (i < end_word)
	{
		if (ft_isdigit(input[i]))
			return (1);
		i++;
	}
	return (0);
}

// Check if the command is valide.

// int	ft_check_lst(t_token *lst)
// {
	
// }

/* Convert char *input in char **prompt and
// convert char **prompt in t_token *lst.*/

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

// int	ft_check_lst(t_token *lst)
// {
// 	if (!ft_is_pipe(lst))
// 		ft_check_lst(lst);
// }

// Test function.

void	ft_print_tab(char **path, int nb_path)
{
	int	i;
	
	i = 0;
	while (i != nb_path)
	{
		printf(YELLOW"path = %s\n"RESET, path[i]);
		i++;
	}
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

char	**ft_clean_path(char **double_tab, int nb_path)
{
	int	i;

	i = 0;
	while (i < nb_path)
	{
		free(double_tab[i]);
		i++;
	}
	free(double_tab);
	return (NULL);
}

char	*ft_add_suf(t_token *lst, int j, char *str)
{
	int	k;

	k = 0;
	str[j] = '/';
	j++;
	while (lst->content[k])
	{
		str[j] = lst->content[k];
		k++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

// Add the cmd at the end of each path.
char	**ft_add_cmd(t_token *lst, char **paths, int nb_path)
{
	char	**new_tab;
	int		size_cmd;
	int		size_line;
	int		i;
	int		j;

	i = 0;
	size_cmd = (int)ft_strlen(lst->content) + 1;
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
		new_tab[i] = ft_add_suf(lst, j, new_tab[i]);
		i++;
	}
	ft_clean_path(paths, nb_path);
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

// int	ft_first_word(t_token *lst)
// {
// 	if ()
// }

// Find $(PATH) with getenv(), check if the cmd exist with acces(),
// run the cmd with execve(). 

// bool	ft_one_cmd(t_token *lst, t_cmd *cmd, char **env)
// {
// 	t_token	*tmp;
// 	char	**paths;
// 	int		nb_path;

// 	tmp = lst;
// 	nb_path = ft_count_path(getenv("PATH"));
// 	printf(GREEN"nb_path = %d\n"RESET, nb_path);
// 	paths = ft_split(getenv("PATH"), ':');
// 	ft_print_tab(paths, nb_path);
// 	printf(RED"-------------------------------------------------------\n"RESET);
// 	paths = ft_add_cmd(lst, paths, nb_path);
// 	ft_print_tab(paths, nb_path);
// 	if (ft_is_bin(paths, nb_path))
// 	{
// 		cmd->pathname = ft_is_bin(paths, nb_path);
// 		printf(RED"Right path = %s\n"RESET, cmd->pathname);
// 		execve(cmd->pathname, cmd->args, env);
// 		return (true);
// 	}
// 	// if (ft_first_word(tmp))
// 	// 	return (true);
// 	// else
// 	// 	return (false);
// 	tmp = tmp->next;
// 	return (true);
// }

// void	ft_multi_cmd(lst)
// {
	
// }

void	ft_print_cmd(t_cmd *lst)
{
	int i;
	while (lst)
	{
		i = 0;
		while (lst->args[i] != NULL)
		{
			printf(RED"cmd = %s | type = %d\n"RESET, lst->args[i], lst->type);
			i++;
		}
		lst = lst->next;
	}
}

int	ft_parsing(char *input, char **env)
{
	int		i;
	int		len_tab;
	char	**prompt;
	t_token	*token;
	t_cmd	*cmd;
	(void)env;

	i = 0;
	cmd = NULL;
	// syntaxe_error(input);
	len_tab = ft_count_word(input);
	if	(ft_strchr(input, '$'))
		input = handle_env_var(input, env);
	return 0;
	prompt = ft_multi_split(input);
	token = ft_tab_to_lst(prompt, len_tab);
	token = ft_handle_quote(token);
	
	// ft_print_lst(token);
	cmd = ft_init_cmd(token);
	// ft_print_cmd(cmd);




	
	/*-------------------useless---------------------------*/
	// ft_print_cmd(cmd);
	// cmd = ft_init_cmd(token);
	// cmd = malloc(sizeof(t_cmd));
	// cmd->args = prompt;
	// while (i < len_tab)
	// 	i++;
	// ft_check_lst(lst);
	// if (ft_is_pipe(lst))
	// 	ft_multi_cmd(lst);
	// else
		// ft_one_cmd(lst, cmd, env);
	return (0);
}
