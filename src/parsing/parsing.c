/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/04 22:12:51 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "minishell.h"

bool	ft_is_pipe(t_token *lst)
{
	int		i;
	t_token	*tmp;

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
		i += 5;
	while (args[i])
	{
		str[j] = args[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*one_line_path(char **paths, t_gmalloc **head)
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
	new_tab = gb_malloc((i + 1) * sizeof (char), head);
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
	// if (cmd->args[0][0] == '\0')
	// 	return (cmd->args);
	if (cmd->args[0][0] == '~' && cmd->args[0][1] == '\0')
	{
		new_tab = malloc(2 * sizeof(char *));
		new_tab[0] = one_line_path(paths, head);
		new_tab[1] = NULL;
	}
	else
	{
		size_cmd = (int)ft_strlen(cmd->args[0]) + 1;
		new_tab = gb_malloc(((nb_path + 1) * sizeof(char *)), head);
		new_tab[nb_path] = NULL;
		while (paths[i] != NULL)
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
	free_prompt(paths, head);
	return (new_tab);
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

int	open_for_each_redir(t_redir **head, t_cmd *cmd,t_mini *mini)
{
	t_redir	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (temp->type == HERE_DOC)
		{
			cmd->fd_here_doc = here_doc(mini, temp->filename, &mini->gmalloc);
			if (cmd->fd_here_doc <= 0)
			{
				if (cmd->fd_here_doc == -1)
				{
					mini->exit_status = 1;
					ft_putstr_fd("error occured during the creation of here document\n", 2);
				}
				return (-1);
			}
		}
		temp = temp->next;
	}
	return (0);
}

int	open_for_each_cmd(t_cmd **head, t_mini *mini)
{
	t_cmd *temp;
	
	temp = *head;
	while (temp != NULL)
	{
		if (open_for_each_redir(&temp->redir, temp, mini) != 0)
			return (-1);
		temp = temp->next;
	}
	return (0);
}

int	ft_parsing(char *input, t_mini *mini)
{
	int		len_tab;
	char	**prompt;

	mini->cmd = NULL;
	if (prompt_is_empty(input))
		return (0);
	if (syntax_error(input))
		return (str_return("minishell : syntax error\n", 2, mini));
	if	(ft_strchr(input, '$'))
	{
		input = handle_env_var(input, mini);
		if (!input || input[0] == '\0')
			return (0);
	}
	prompt = ft_multi_split(input, &mini->gmalloc);
	// print_tab_char(prompt);
	len_tab = count_tab(prompt);
	mini->token = ft_tab_to_lst(prompt, len_tab, &mini->gmalloc);
	mini->token = ft_handle_quote(&mini->token);
	mini->nb_pipe = ft_count_pipe(&mini->token);
	// ft_print_lst(mini->token);
	mini->cmd = ft_init_cmd(&mini->token, &mini->gmalloc);
	if (open_for_each_cmd(&mini->cmd, mini) != 0)
	{
		free_cmd(mini->cmd, &mini->gmalloc);
		return (0);
	}
	unblock_sig_quit();
	if (mini->nb_pipe > 0)
		pipex(mini->cmd, mini, mini->nb_pipe, &mini->gmalloc);
	else
		ft_one_cmd(mini->cmd, mini, &mini->gmalloc);
	// printf("cmd->args = %s\n", mini->cmd->args[0]);
	free_cmd(mini->cmd, &mini->gmalloc);
	return (0);
}
