/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:23:55 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 16:15:38 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		g_sig_flag = 2;
	}
}

void	unblock_sig_quit(void)
{
	struct sigaction	sig_quit;

	ft_bzero(&sig_quit, sizeof(sig_quit));
	sig_quit.sa_handler = &handle_quit;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	block_sig_quit(void)
{
	struct sigaction	sig_quit;

	ft_bzero(&sig_quit, sizeof(sig_quit));
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_quit, NULL);
}
