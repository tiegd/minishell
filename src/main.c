/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:20:41 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/16 16:31:58 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
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
	return (nb_pipe);
}

static int	test_count_args(char *input)
{
	int	i;
	int	count;
	
	i = 0;
	count = 1;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '|')
		{
			i++;
			if (input[i] == '|')
				count++;
		}
		i++;
	}
	printf("count = %d\n", count);
	return (count + 1);
}

static void	test_fill_cmd(t_cmd *cmd, char *input)
{
	int	nb_arg;

	nb_arg = test_count_args(input);
	cmd->args = ft_multi_split(input, ' ', '|');
	ft_print_tab(cmd->args, nb_arg);
}

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
	while (1)
	{
		input = readline("minizeub > ");
		// if (!ft_parsing(input, env))
		// {
		// 	return (1);
		// 	printf("Error input\n");
		// }
		nb_pipe = test_count_pipe(input);
		test_fill_cmd(cmd, input);
		(void)env;
		// pipex(cmd, env, nb_pipe, lst);
	}
	return (0);
}
