/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:34:15 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/25 11:21:31 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	ft_count_pipe(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		count;

	tmp = cmd;
	count = 0;
	while (tmp->next)
	{
		count++;
		tmp = tmp->next;
	}
	printf("count = %d\n", count);
	return (count);
}

void	wait_children(pid_t pid_last, t_cmd *cmd)
{
	int	status;
	
	waitpid(pid_last, &status, 0);
	if (WIFEXITED(status) != 0)
		cmd->error = WEXITSTATUS(status);
	while (1)
	{
		if (wait(NULL) == -1)
			break ;
	}
}
