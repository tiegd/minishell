/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:02:52 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/04 22:57:34 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(char *s1, char *s2)
{
	int	i;
	
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] - s2[i] == 0)
		return (1);
	return (0);
}
//checker si c'est une option ou pas
int	is_option(char	*str)
{
	int	i;
	
	i = 0;
	if (ft_strcmp(str, "-n"))
		return (1);
	if (str[i] == '-')
	{
		i++;
		while(str[i] != '\0')
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(t_cmd *cmd)
{
	int		i;
	// int		j;
	bool	with_option;

	i = 1;
	// j = 0;

	with_option = false;
	// printf("|%s|\n", cmd->args[i]);
	//verifier qu'il y a une option dans la commande.
	if (cmd->args[i] && is_option(cmd->args[i]))
		with_option = true;
	//tant que les options sont -n ou -nnnnnnn continuer jusqu'à l'argument suivant.
	while (cmd->args[i] && is_option(cmd->args[i]))
		i++;
	//checker si il y a un autre argument, si il n'y en a pas dire que la commande est valide mais renvoyer NULL.
	if (cmd->args[i] == NULL)
	{
		if (with_option == true)
			printf("");
		else
			printf("\n");
		return ;
	}
	//si il y a encore des arguments les prints les un a la suite des autres avec 1 espace entre chaque
	if (cmd->args[i] != NULL)
	{
		while (cmd->args[i] != NULL)
		{
			//regarder si c'est le dernier argument ou pas
			if (cmd->args[i + 1] == NULL)
			{
				//enlever le \n en fonction
				if(with_option == true)
					printf("%s", cmd->args[i]);
				else
					printf("%s\n", cmd->args[i]);
			}
			else
				printf("%s ", cmd->args[i]);
			i++;
			// //sinon printf l'argument avec un espace pour le prochain argument
			// else if (cmd->quote == 2)
			// 	printf("%s", cmd->args[i]);
		}
	}
	// if (cmd->args[1][0] == '$' && cmd->args[1][1] == '?' && cmd->args[1][2] == '\0')
	// 	printf("%d", mini->exit_status);
	else
	{
		printf("\n");
	}
	
}
