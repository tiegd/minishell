/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:20:41 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/16 13:17:45 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "minishell.h"

int	ft_count_pipe(char *input)
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

int	main(int ac, char **av, char **env)
{
	char	*input;
	int		nb_pipe;

	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("minizeub > ");
		if (!ft_parsing(input, env))
		{
			return (1);
			printf("Error input\n");
		}
		nb_pipe = ft_count_pipe(input);
		// ft_fill_cmd_test(cmd);
		// exec_one_pipe(cmd, env, nb_pipe, lst);
	}
	return (0);
}
