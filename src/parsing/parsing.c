/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/27 15:09:58 by jpiquet          ###   ########.fr       */
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

char	*one_line_path(char **paths)
{
	char	*new_tab;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	
	while (paths[0][i] && count <= 2)
	{
		if (paths[0][i] == '/')
			count++;
		if (count <= 2)
			i++;
	}
	new_tab = malloc((i + 1) * sizeof (char));
	while (j < i)
	{
		new_tab[j] = paths[0][j];
		j++;
	}
	new_tab[j] = '\0';
	return (new_tab);
}

// Add the cmd at the end of each path.
char	**ft_add_cmd(char **paths, int nb_path, t_cmd *cmd, t_gmalloc **head)
{
	char	**new_tab;
	int		size_cmd;
	int		size_line;
	int		i;
	int		j;

	i = 0;
	if (cmd->args[0][0] == '~' && cmd->args[0][1] == '\0')
	{
		new_tab = malloc(2 * sizeof(char *));
		new_tab[0] = one_line_path(paths);
	}
	else
	{
		size_cmd = (int)ft_strlen(cmd->args[0]) + 1;
		new_tab = gb_malloc(((nb_path + 1) * sizeof(char *)), head);
		while (i < nb_path)
		{
			j = 0;
			size_line = (int)ft_strlen(paths[i]) + size_cmd + 1;
			new_tab[i] = gb_malloc((size_line * sizeof(char)), head);
			while (paths[i][j])
			{
				new_tab[i][j] = paths[i][j];
				j++;
			}
			new_tab[i] = ft_add_suf(j, new_tab[i], cmd->args[0]);
			i++;
		}
	}
	free_split(paths, nb_path, head);
	// free_double_tab(paths, nb_path,);
	return (new_tab);
}

char	*ft_path_line(char **env, t_gmalloc **head)
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
			path = gb_malloc(((len + 1) * sizeof(char)), head);
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

void	open_for_each_redir(t_redir **head, t_mini *mini)
{
	t_redir	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->type == HERE_DOC)
			{
				mini->cmd->fd_here_doc = here_doc(mini, temp->filename, &mini->gmalloc);
			}
			temp = temp->next;
	}
}

void	open_for_each_cmd(t_cmd **head, t_mini *mini)
{
	t_cmd *temp;
	
	temp = *head;
	while (temp != NULL)
	{
		open_for_each_redir(&temp->infiles, mini);
		temp = temp->next;
	}
}

int	ft_parsing(char *input, t_mini *mini)
{
	int		len_tab;
	int		nb_pipe;
	char	**prompt;

	mini->cmd = NULL;
	if (prompt_is_empty(input))
		return (0);
	if (syntax_error(input))
		return (str_return("minishell : syntax error\n", 2, mini));
	if	(ft_strchr(input, '$'))
		input = handle_env_var(input, mini);
	prompt = ft_multi_split(input, &mini->gmalloc);
	len_tab = count_tab(prompt);
	mini->token = ft_tab_to_lst(prompt, len_tab, &mini->gmalloc);
	mini->token = ft_handle_quote(mini->token);
	mini->cmd = ft_init_cmd(mini->token, &mini->gmalloc);
	open_for_each_cmd(&mini->cmd, mini);
	nb_pipe = ft_count_pipe(&mini->token);
	unblock_sig_quit();
	if (nb_pipe > 0)
		pipex(mini->cmd, mini, nb_pipe, &mini->gmalloc);
	else
		ft_one_cmd(mini->cmd, mini, &mini->gmalloc);
	return (0);
}
