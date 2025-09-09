/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:23:55 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 17:53:44 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

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
