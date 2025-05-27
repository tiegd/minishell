/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:09:18 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/27 19:53:43 by jpiquet          ###   ########.fr       */
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

/*--------------------------EXPEND------------------------*/

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	char *exp;
// 	bool malloc_error;

// 	malloc_error = false;
// 	exp = expend("bonjour$HOMEx'''", env, &malloc_error);
// 	printf("exp = %s\n", exp);
// 	return (0);
// }

/*--------------------------ENV------------------------*/

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	if (ft_strcmp(av[1], "env"))
// 		ft_env(env, STDOUT_FILENO);
// 	return (0);
// }

/*--------------------------ECHO------------------------*/

// int main(int ac, char **av, char **env)
// {
// 	int i;
// 	int j;
// 	t_cmd cmd;

// 	i = 1;
// 	j = 0;
// 	cmd.valid = true;
// 	cmd.args = malloc(sizeof(char *) * ac);
// 	cmd.malloc_error = false;
// 	cmd.quote = 0;
// 	while (i < ac)
// 	{
// 		if (ft_strchr(av[i], '$'))
// 		{
// 			cmd.expend = expend(av[i], env, &cmd.malloc_error);
// 			cmd.is_env_var = true;
// 		}
// 		cmd.args[j] = ft_strdup(av[i]);
// 		i++;
// 		j++;
// 	}
// 	cmd.args[j] = NULL;
// 	ft_echo(&cmd);
// 	if (cmd.valid == false)
// 		printf("error\n");
// 	return (0);
// }

/*--------------------------EXPORT------------------------*/

int main(int ac, char **av, char **env)
{
	int i;
	char **new_env;
	(void)ac;
	(void)av;

	i = 0;
	new_env = ft_export(env, "A=bonjour$HOME$LANG");
	// new_env = ft_export(new_env, av[3]);
	// new_env = ft_export(new_env, av[4]);
	ft_env(new_env, 1);
	return (0);
}