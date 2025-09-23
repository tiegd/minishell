/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:02:52 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 13:17:58 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include <stdio.h>

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

//check if it's an option or not.

static int	is_option(char	*str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "-n"))
		return (1);
	if (str[i] == '-')
	{
		i++;
		if (str[i] == '\0')
			return (0);
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

static void	arg_empty(bool with_option)
{
	if (with_option == true)
		return ;
	else
		ft_putstr_fd("\n", 1);
}

static void	echo_print_args(char **args, int *i, t_gmalloc **head, bool with_option)
{
	if (args[(*i)] != NULL)
	{
		while (args[*i] != NULL)
		{
			if (args[*i + 1] == NULL)
			{
				if (with_option == true)
					ft_putstr_fd(args[*i], STDOUT_FILENO);
				else
					print_with_new_line(args[*i], head);
			}
			else
				print_with_space(args[*i], head);
			(*i)++;
		}
	}
	else
		ft_putstr_fd("\n", 1);
}

/*Check that there is an option in the command.
As long as the options are -n or -nnnnnnn, continue to the next argument.
Check if there is another argument; if there isn't, say that the command 
is valid but return NULL.
If there are still arguments, print them one after the other with 
1 space between each one, check if it is the last argument or not,
remove the \n accordingly.
*/

void	ft_echo(t_cmd *cmd, t_gmalloc **head)
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
	echo_print_args(cmd->args, &i, head, with_option);
}
