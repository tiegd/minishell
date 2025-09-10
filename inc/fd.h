/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:10:26 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/10 18:28:25 by jpiquet          ###   ########.fr       */
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
void	ft_dup_out(t_mini *mini);
int		close_all_here_doc(int *here_doc_list);

#endif
