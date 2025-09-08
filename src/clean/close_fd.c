/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:44:51 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/08 15:53:06 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int infile, int outfile)
{
	if (infile > 0)
	{
		if (close(infile) == -1)
		{
			rl_clear_history();
			exit(1);
		}
	}
	if (outfile > 1)
	{
		if (close(outfile) == -1)
		{
			rl_clear_history();
			exit(1);
		}
	}
	
}
