/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:09:18 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/23 15:59:12 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_cmd(t_cmd cmd)
// {
// 	int i = 0;
// 	while (cmd.args[i] != NULL)
// 	{
// 		printf("%s\n", cmd.args[i]);
// 		i++;
// 	}
// }

//POUR EXPEND
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	expend("bonjour$PATHer'''", env);
	return (0);
}

// //POUR ENV

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	if (ft_strcmp(av[1], "env"))
// 		ft_env(env, STDOUT_FILENO);
// 	return (0);
// }

// //POUR ECHO

// int main(int ac, char **av)
// {
// 	int i;
// 	int j;
// 	t_cmd cmd;

// 	i = 1;
// 	j = 0;
// 	cmd.valid = true;
// 	cmd.args = malloc(sizeof(char *) * ac);
// 	while (i < ac)
// 	{
// 		//printf("error\n");
// 		cmd.args[j] = ft_strdup(av[i]);
// 		i++;
// 		j++;
// 	}
// 	cmd.args[j] = NULL;
// 	ft_echo(&cmd);
// 	//print_cmd(cmd);
// 	if (cmd.valid == false)
// 		printf("error\n");
// 	return (0);
// }
