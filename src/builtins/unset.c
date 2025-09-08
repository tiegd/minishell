/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:02:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/04 21:51:19 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**unset(char *var, char **old_env, t_gmalloc **head)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = gb_malloc(sizeof(char *) * (nb_var(old_env) + 1), head);
	while(old_env[i] != NULL)
	{
		if (env_var_cmp(old_env[i], var) == 1 || env_var_cmp(var, old_env[i]) == 2)
		{
			if (old_env)
				i++;
			else
				break ;
		}
		if (old_env[i] == NULL)
			break ;
		new_env[j] = gb_strdup(old_env[i], head);
		i++;
		j++;
	}
	new_env[j] = NULL;
	free_double_tab(old_env, nb_var(old_env), head);
	return (new_env);
}

char	**loop_unset(char **env, char **args, t_mini *mini, t_gmalloc **head)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		env = unset(args[i], env, head);
		i++;
	}
	mini->exit_status = 0;
	return (env);
}

// int main(int ac, char **av, char **env)
// {
// 	t_gmalloc *gmalloc;
// 	(void)ac;

// 	gmalloc = NULL;
// 	av += 1;
// 	printf("before\n\n");
// 	loop_unset(env, av, gmalloc);
// 	printf("\nafter\n\n");
// 	print_tab_char(env);
// 	return (0)
// }
