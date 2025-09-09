/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:20:41 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/09 18:31:32 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "gblib.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

int	g_sig_flag = 0;

char	**dup_env(char **old_env, t_gmalloc **gmalloc)
{
	int		i;
	char	**new_env;
	int		len_tab;

	i = 0;
	len_tab = ft_nb_path(old_env);
	new_env = gb_malloc(sizeof(char *) * (len_tab + 1), gmalloc);
	while (old_env[i])
	{
		new_env[i] = gb_strdup(old_env[i], gmalloc);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	check_interactive_mode(void)
{
	if (isatty(STDIN_FILENO) == 0 || isatty(STDOUT_FILENO) == 0)
	{
		ft_putstr_fd("Please launch minishell in interactive mode.\n", 2);
		exit(1);
	}
}

void	init_mini(t_mini *mini, char **env)
{
	mini->gmalloc = NULL;
	mini->cmd = NULL;
	if (!*env || !env)
		mini->env = env_dash_i(&mini->gmalloc);
	else
		mini->env = dup_env(env, &mini->gmalloc);
	mini->exit_status = 0;
	mini->dup_std[0] = 0;
	mini->dup_std[1] = 0;
}

void	init_start(t_mini *mini, char **env)
{
	check_interactive_mode();
	set_sig_action();
	block_sig_quit();
	init_mini(mini, env);
}

int	main(int ac, char **av, char **env)
{
	char				*line;
	t_mini				mini;

	ac = 0;
	av = NULL;
	init_start(&mini, env);
	while (1)
	{
		g_sig_flag = 0;
		line = readline("minishell Platini ~ ");
		if (g_sig_flag == 1)
		{
			mini.exit_status = 130;
			continue ;
		}
		if (!line)
			ft_exit(NULL, &mini, &mini.gmalloc);
		if (*line)
			add_history(line);
		if (ft_parsing(line, &mini))
			return (1);
		free(line);
	}
	return (0);
}
