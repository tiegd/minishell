/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:41:10 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 10:28:33 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "gblib.h"
#include "parsing.h"
#include "builtins.h"

/*compares strings up to the character passed as a parameter*/

int	strcmp_until_char(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i - 1] - s2[i - 1] == 0 && s2[i] == c)
		return (1);
	return (0);
}

char	*add_double_quote(char *res, t_gmalloc **head)
{
	int		i;
	int		len;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	len = ft_strlen(res);
	temp = gb_malloc((len + 3) * sizeof(char), head);
	temp[i] = '"';
	i++;
	while (res[j])
		temp[i++] = res[j++];
	temp[i++] = '"';
	temp[i] = '\0';
	return (temp);
}

int	has_special(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_special(str[i]))
			return (1);
		i++;
	}
	return (0);
}

/*retrieves the result of an environment variable*/

char	*env_result(char *env, t_gmalloc **head)
{
	int		i;
	char	*res;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] && env[i] == '=')
		i++;
	env += i;
	res = gb_strdup(env, head);
	if (has_special(res) || has_single_quote(res))
		res = add_double_quote(res, head);
	else if (has_double_quote(res))
		res = add_single_quote(res, head);
	return (res);
}

// For count the number of char for ft_itoa().

int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}
