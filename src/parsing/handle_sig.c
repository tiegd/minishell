/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:23:55 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/27 16:11:10 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event_hook(void)
{
	return (0);
}

void	handle_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		sig_flag = 2;
	}
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		sig_flag = 1;
		rl_done = 1;
	}
}

void	unblock_sig_quit(void)
{
	struct	sigaction sig_quit;

	ft_bzero(&sig_quit, sizeof(sig_quit));
	sig_quit.sa_handler = &handle_quit;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	block_sig_quit(void)
{
	struct	sigaction sig_quit;
	
	ft_bzero(&sig_quit, sizeof(sig_quit));
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	set_sig_action(void)
{
	struct	sigaction sig_int;

	ft_bzero(&sig_int, sizeof(sig_int));
	sig_int.sa_handler = &handle_sig;
	sigaction(SIGINT, &sig_int, NULL);
	rl_event_hook = event_hook;
}
