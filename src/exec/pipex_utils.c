/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:34:15 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/08 17:10:33 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count the number of '|' in the prompt.

int	count_pipe(t_token **token)
{
	t_token	*tmp;
	int		count;

	tmp = *token;
	count = 0;
	while (tmp->next)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	wait_children(pid_t pid_last, t_mini *mini)
{
	int	status;

	waitpid(pid_last, &status, 0);
	if (WIFEXITED(status) != 0 && g_sig_flag == 0)
		mini->exit_status = WEXITSTATUS(status);
	while (1)
	{
		if (wait(NULL) == -1)
			break ;
	}
	if (g_sig_flag == 2)
		mini->exit_status = 131;
	if (g_sig_flag == 1)
		mini->exit_status = 130;
}
