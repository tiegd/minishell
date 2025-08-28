/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:20:41 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/28 12:52:53 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_flag = 0;

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
	if (!*env || !env)
		mini->env = env_dash_i(&mini->gmalloc);
	else
		mini->env = dup_env(env, &mini->gmalloc);
	mini->exit_status = 0;
}

int	main(int ac, char **av, char **env)
{
	char				*line;
	t_mini				mini;
	(void)ac;
	(void)av;

	check_interactive_mode();
	set_sig_action();
	block_sig_quit();
	init_mini(&mini, env);
	while (1)
	{
		sig_flag = 0;
		block_sig_quit();
		line = readline("miniprout >>");
		if (sig_flag == 1)
		{
			mini.exit_status = 130;
			continue ;
		}
		if (!line)
			ft_exit(NULL, 0, &mini.gmalloc);
		if (*line)
			add_history(line);
		if (ft_parsing(line, &mini))
			return (1);
		free(line);
	}
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	struct sigaction	sa_ctrl_c;
// 	// struct sigaction	sa_ctrl_d;
// 	char				*line;
// 	t_mini				mini;
// 	(void)ac;
// 	(void)av;

// 	if (isatty(STDIN_FILENO) == 0)
// 	{
// 		ft_putstr_fd("Please launch minishell in interactive mode.\n", 2);
// 		exit(1);
// 	}
	// sa_ctrl_c.sa_handler = &handle_ctrl_c;
// 	sigemptyset(&sa_ctrl_c.sa_mask);
// 	sa_ctrl_c.sa_flags = SA_RESTART;
// 	mini.gmalloc = NULL;
// 	if (!*env || !env)
// 		mini.env = env_dash_i(&mini.gmalloc);
// 	else
// 		mini.env = dup_env(env, &mini.gmalloc);
// 	sigaction(SIGINT, &sa_ctrl_c, NULL);
// 	mini.exit_status = 0;
// 	while ((line = readline(GREEN"minizeub > "RESET)) != NULL)
// 	{
// 		if (*line)
// 			add_history(line);
// 		if (ft_parsing(line, &mini))
// 			return (1);
// 		free(line);
// 	}
// 	if (!line)
// 		ft_exit(NULL, 0, &mini.gmalloc);
// 	return (0);
// }
