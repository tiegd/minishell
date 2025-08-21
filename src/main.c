/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:20:41 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/21 12:48:51 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	test_count_pipe(char *input)
// {
// 	int	i;
// 	int	nb_pipe;

// 	i = 0;
// 	nb_pipe = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '|')
// 			nb_pipe++;
// 		i++;
// 	}
// 	printf(CYAN"nb_pipe = %d\n"RESET, nb_pipe);
// 	return (nb_pipe);
// }

// static int	test_count_args(char *input)
// {
// 	int	i;
// 	int	count;
	
// 	i = 0;
// 	count = 1;
// 	while (input[i])
// 	{
// 		while (input[i] == ' ' || input[i] == '|')
// 		{
// 			i++;
// 			if (input[i] == '|')
// 				count++;
// 		}
// 		i++;
// 	}
// 	printf(YELLOW"nb_args = %d\n"RESET, count);
// 	return (count + 1);
// }

// static void	test_fill_args(t_cmd *cmd, t_token *lst, int nb_pipe)
// {
// 	t_cmd	*tmp;
// 	int		count;
// 	int		i;
// 	char	*new_tab;
	
// 	count = 0;
// 	i = 0;
// 	while (lst->next)
// 	{
// 		while (lst->content[i])
// 		{
// 			i++;
// 			if (lst->content[i] == '|')
// 				count++;
// 		}
// 	}
// 	new_tab = malloc((count + 1) * sizeof(char**));
// }

// static void	test_fill_cmd(t_cmd *cmd, t_token *lst, int nb_pipe)
// {
// 	// t_token	*lst;
// 	// int		nb_arg;
// 	// int		len;
// 	char	**tab;

// 	(void)cmd;
// 	// nb_arg = test_count_args(input);
// 	// tab = ft_multi_split(input, ' ', '\t');
// 	test_fill_args(cmd, lst, nb_pipe);
// 	// ft_print_tab(cmd->args, nb_arg);
// }

void	handle_ctrl_c(int sig)
{
	(void)sig;
	// printf("");
	// rl_replace_line("\n", 1);
	rl_on_new_line();
	rl_redisplay();
	// rl_redisplay();
	// printf("");
}

char	**dup_env(char **old_env, t_gmalloc **gmalloc)
{
	int		i;
	char	**new_env;
	int		len_tab;

	i = 0;
	len_tab = ft_nb_path(old_env);
	// printf("%d\n", len_tab);
	new_env = gb_malloc(sizeof(char *) * (len_tab + 1), gmalloc);
	while (old_env[i])
	{
		new_env[i] = gb_strdup(old_env[i], gmalloc);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sa_ctrl_c;
	char				*line;
	t_mini				mini;
	(void)ac;
	(void)av;

	sa_ctrl_c.sa_handler = &handle_ctrl_c;
	sa_ctrl_c.sa_flags = SA_RESTART;
	mini.gmalloc = NULL;
	if (!env)
		mini.env = env_dash_i();
	else
		mini.env = dup_env(env, &mini.gmalloc);
	sigaction(SIGINT, &sa_ctrl_c, NULL);
	mini.exit_status = 0;
	while ((line = readline(GREEN"minizeub > "RESET)) != NULL)
	{
		// sigaction(SIGINT, &sa_ctrl_c, NULL);
		if (*line)
			add_history(line);
		if (ft_parsing(line, &mini))
			return (1);
		free(line);
	}
	if (!line)
		ft_exit(NULL, 0, &mini.gmalloc);
	return (0);
}
