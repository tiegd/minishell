/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:25:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/05/20 17:10:18 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		i;
	char	*line;

	i = 0;
	while (i != 3)
	{
		line = readline(0);
		add_history(line);
		free(line);
		i++;
	}
	return (0);
}
