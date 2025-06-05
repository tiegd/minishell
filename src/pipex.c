/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:51:32 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/05 15:23:53 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "minishell.h"

static void	first_pipe(t_cmd *cmd, char *envp[], t_fd *fd, int i)
{
	return ;
}

static void	last_pipe(t_cmd *cmd, char *envp[], t_fd *fd, int i)
{
	return ;
}

void	pipex(t_cmd *cmd, char *envp[], t_fd fd)
{
	first_pipe(cmd, envp, &fd, 0);
	last_pipe(cmd, envp, &fd, 1);
}
    