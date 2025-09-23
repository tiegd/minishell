/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:19:19 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 10:28:40 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "gblib.h"

int	has_single_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SQ)
			return (1);
		i++;
	}
	return (0);
}

int	has_double_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DQ)
			return (1);
		i++;
	}
	return (0);
}

char	*add_single_quote(char *res, t_gmalloc **head)
{
	int		i;
	int		len;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	len = ft_strlen(res);
	temp = gb_malloc((len + 3) * sizeof(char), head);
	temp[i] = SQ;
	i++;
	while (res[j])
		temp[i++] = res[j++];
	temp[i++] = SQ;
	temp[i] = '\0';
	return (temp);
}
