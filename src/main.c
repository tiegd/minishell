/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:20:41 by gaducurt          #+#    #+#             */
/*   Updated: 2025/07/03 14:38:36 by jpiquet          ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char	*line;
	(void)ac;
	(void)av;

	while ((line = readline("minizeub > ")) != NULL)
	{
		if (*line)
		{
			add_history(line);
		}
		if (ft_parsing(line, env))
			return (1);
	}
	return (0);
}
