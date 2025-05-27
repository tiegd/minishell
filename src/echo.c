/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:02:52 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/26 15:27:53 by jpiquet          ###   ########.fr       */
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

void	echo_dollar(char *args, char *expend)
{
	int	i;

	i = 0;
	while (args[i] && args[i] != '$')
	{
		write(1, &args[i], 1);
	}
	printf("%s", expend);
}

void	ft_echo(t_cmd *cmd)
{
	int		i;
	int		j;
	bool	with_option;

	i = 1;
	j = 0;

	with_option = false;
	//verifier qu'il y a une option dans la commande.
	if (cmd->args[i] && is_option(cmd->args[i]))
	{
		with_option = true;
	}
	//tant que les options sont -n ou -nnnnnnn continuer jusqu'à l'argument suivant.
	while (cmd->args[i] && is_option(cmd->args[i]))
	{
		i++;
	}
	//checker si il y a un autre argument, si il n'y en a pas dire que la commande est valide mais renvoyer NULL.
	if (cmd->args[i] == NULL)
	{
		cmd->valid = true;
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
			//regarder si il y a une variable d'environnement et qu'elle n'est pas entre single quote.
			if (cmd->is_env_var == true && cmd->quote != 1)
			{
				echo_dollar(cmd->args[i], cmd->expend); //print la variable d'environnement
				if (cmd->args[i + 1] == NULL)
				{
					printf("\n"); //mettre un \n si c'est le dernier arguement
					return ;
				}
				// write(1, "HHHHHH", 7);//sinon print un espace pour le prochain arguments
				i++;
			}
			//regarder si c'est le dernier argument ou pas
			if (cmd->args[i + 1] == NULL)
			{
				//enlever le \n en fonction
				if(with_option == true)
					printf("%s", cmd->args[i]);
				else
					printf("%s\n", cmd->args[i]);
			}
			//sinon printf l'argument avec un espace pour le prochain argument
			else if (cmd->quote == 2)
				printf("%s", cmd->args[i]);
			else
				printf("%s ", cmd->args[i]);
			i++;
		}
	}
	else
	{
		printf("\n");
	}
}
