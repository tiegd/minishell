/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:03:53 by gaducurt          #+#    #+#             */
/*   Updated: 2025/05/26 08:56:49 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_check_prompt(char *input)
{
	int		i;
	char	**prompt;

	i = 0;
	prompt = ft_multi_split(input, ' ', '\t');
	while (prompt[i])
	{
		printf("prompt[%d] = %s\n", i, prompt[i]);
		i++;
	}
	return (1);
}
