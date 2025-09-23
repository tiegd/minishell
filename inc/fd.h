/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:10:26 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/23 13:39:50 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_H
# define FD_H

# include "struct.h"

/*------------REDIR------------*/

void	redir_first_pipe(t_mini *mini, t_cmd *cmd, int *pipefd);
void	redir_middle_pipe(t_mini *mini, t_cmd *cmd, int *pipefd);
void	redir_last_pipe(t_mini *mini, t_cmd *cmd, int *pipefd);
void	redir_one(t_cmd *cmd, t_mini *mini);
int		is_close(t_cmd *cmd);

/*------------FD------------*/

int		ft_open_fd(t_cmd *cmd, t_mini *mini);
int		ft_close_fd(t_cmd *cmd, int *pipefd);
void	close_fds(int infile, int outfile);
int		close_all_here_doc(int *here_doc_list);
void	close_both_fd(int fd1, int fd2);

#endif
