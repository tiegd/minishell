/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:23:55 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 17:53:35 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <readline/readline.h>

int	event_hook(void)
{
	return (0);
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_flag = 1;
		rl_done = 1;
	}
}

void	set_sig_action(void)
{
	struct sigaction	sig_int;

	ft_bzero(&sig_int, sizeof(sig_int));
	sig_int.sa_handler = &handle_sig;
	sigaction(SIGINT, &sig_int, NULL);
	rl_event_hook = event_hook;
}

void	block_sig_int(void)
{
	struct sigaction	sig_int;

	ft_bzero(&sig_int, sizeof(sig_int));
	sig_int.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig_int, NULL);
}
