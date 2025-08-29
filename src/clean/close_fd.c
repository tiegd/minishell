/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:44:51 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/29 13:46:08 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int infile, int outfile)
{
	if (infile > 1)
	{
		if (close(infile) == -1)
			exit(1);
	}
	if (outfile > 1)
	{
		if (close(outfile) == -1)
			exit(1);
	}
}
