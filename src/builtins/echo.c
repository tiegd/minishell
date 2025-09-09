/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:02:52 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 08:24:11 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
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
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	arg_empty(bool with_option)
{
	if (with_option == true)
		printf("");
	else
		printf("\n");
}

void	echo_print_args(char **args, int *i, bool with_option)
{
	if (args[(*i)] != NULL)
	{
		while (args[*i] != NULL)
		{
			if (args[*i + 1] == NULL)
			{
				if (with_option == true)
					printf("%s", args[*i]);
				else
					printf("%s\n", args[*i]);
			}
			else
				printf("%s ", args[*i]);
			(*i)++;
		}
	}
	else
		printf("\n");
}

/*verifier qu'il y a une option dans la commande.
Tant que les options sont -n ou -nnnnnnn continuer jusqu'à l'argument suivant.
Checker si il y a un autre argument, si il n'y en a pas dire que la commande 
est valide mais renvoyer NULL.
Si il y a encore des arguments les prints les un a la suite des autres avec 
1 espace entre chaque regarder si c'est le dernier argument ou pas
enlever le \n en fonction*/

void	ft_echo(t_cmd *cmd)
{
	int		i;
	bool	with_option;

	i = 1;
	with_option = false;
	if (cmd->args[i] && is_option(cmd->args[i]))
		with_option = true;
	while (cmd->args[i] && is_option(cmd->args[i]))
		i++;
	if (cmd->args[i] == NULL)
	{
		arg_empty(with_option);
		return ;
	}
	echo_print_args(cmd->args, &i, with_option);
}
