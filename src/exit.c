/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:02:22 by gaducurt          #+#    #+#             */
/*   Updated: 2025/06/12 17:02:47 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_pid_error(int *pipefd, t_cmd *cmd)
{
	
}

void	exit_tab(t_cmd *cmd, t_token *lst, int code)
{
	free_struct(cmd, lst);
	exit(code);
}

void	exit_fd(int fd, t_cmd *cmd, t_token *lst)
{
	if (fd > 0)
		close(fd);
	free_struct(cmd, lst);
	perror("No such file or directory");
	exit(EXIT_FAILURE);
}
