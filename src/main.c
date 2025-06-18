/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:20:41 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/18 10:02:47 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	test_count_pipe(char *input)
{
	int	i;
	int	nb_pipe;

	i = 0;
	nb_pipe = 0;
	while (input[i])
	{
		if (input[i] == '|')
			nb_pipe++;
		i++;
	}
	printf(CYAN"nb_pipe = %d\n"RESET, nb_pipe);
	return (nb_pipe);
}

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

int	main(int ac, char **av, char **env)
{
	char	*input;
	int		nb_pipe;
	t_cmd	*cmd;
	t_token	*lst;

	(void)ac;
	(void)av;
	lst = malloc(sizeof(t_token));
	cmd = malloc(sizeof(t_cmd));
	while ((input = readline("mishell > ")) != NULL)
	{
		if (*input)
			add_history(input);
		if (!ft_parsing(input, env, lst))
		{
			printf("Error input\n");
			return (1);
		}
		nb_pipe = test_count_pipe(input);
		// test_fill_cmd(cmd, input, nb_pipe);
		// (void)env;
		if (nb_pipe > 0)
			pipex(cmd, env, nb_pipe, lst); 
	}
	return (0);
}
