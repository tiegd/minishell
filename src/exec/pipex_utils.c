/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:34:15 by gaducurt          #+#    #+#             */
/*   Updated: 2025/08/28 14:11:12 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Count the number of '|' in the prompt.
int	ft_count_pipe(t_token **token)
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

	// status = 0;
	waitpid(pid_last, &status, 0);
	if (WIFEXITED(status) != 0)
		mini->exit_status = WEXITSTATUS(status);
	if (sig_flag == 2)
		mini->exit_status = 131;
	if (sig_flag == 1)
		mini->exit_status = 130;
	while (1)
	{
		if (wait(NULL) == -1)
			break ;
	}
}
