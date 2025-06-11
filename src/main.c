/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:20:41 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/11 11:01:56 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;

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
	}
	return (0);
}
