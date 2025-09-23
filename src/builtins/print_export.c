/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:10:02 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 13:26:08 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "gblib.h"
#include "exec.h"

static char	*gb_strdup_free_src(char *s, t_gmalloc **gmalloc)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(s);
	dest = gb_malloc(sizeof(char) * len + 1, gmalloc);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	gfree(s, gmalloc);
	return (dest);
}

static int	real_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

static void	sort_env(char **env, t_gmalloc **head)
{
	char	*temp;
	t_sort	sort;

	sort.i = 0;
	sort.len = nb_var(env);
	while (sort.i < sort.len - 1)
	{
		sort.j_min = sort.i;
		sort.j = sort.i + 1;
		while (sort.j < sort.len)
		{
			if (real_strcmp(env[sort.j], env[sort.j_min]) < 0)
				sort.j_min = sort.j;
			sort.j++;
		}
		if (sort.j_min != sort.i)
		{
			temp = gb_strdup_free_src(env[sort.i], head);
			env[sort.i] = gb_strdup_free_src(env[sort.j_min], head);
			env[sort.j_min] = gb_strdup_free_src(temp, head);
		}
		sort.i++;
	}
}

void	print_export(char **env, t_mini *mini, t_gmalloc **head)
{
	int	i;
	int	j;

	i = 0;
	sort_env(env, head);
	while (env[i])
	{
		j = 0;
		ft_putstr_fd("export ", 1);
		while (env[i][j] && env[i][j] != '=')
			ft_putchar_fd(env[i][j++], 1);
		if (env[i][j] != '\0')
		{
			ft_putchar_fd(env[i][j++], 1);
			ft_putchar_fd('"', 1);
			while (env[i][j])
				ft_putchar_fd(env[i][j++], 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
	mini->exit_status = 0;
}
