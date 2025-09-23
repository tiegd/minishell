/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:54:14 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/23 09:34:47 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

# include "struct.h"

/*------------CLEAN------------*/

void	free_token(t_token *lst, t_gmalloc **head);
void	free_redir(t_redir *redir, t_gmalloc **head);
char	**free_double_tab(char **tab, int nb_agrs, t_gmalloc **head);
void	free_cmd(t_cmd *cmd, t_gmalloc **head);
void	print_not_valid_identifier(char *str, t_mini *mini);
void	print_no_such_file(char *str, t_mini *mini);
void	print_error_exit_arg(char *str, t_gmalloc **head);
char	**free_prompt(char **double_tab, t_gmalloc **head);
void	free_one_cmd(t_cmd *cmd, t_gmalloc **head);

/*------------EXIT------------*/

void	exit_pid_error(int *pipefd, t_mini *mini);
void	exit_tab(t_cmd *cmd, t_mini *mini, int code, int *pipefd);
void	exit_fd(t_cmd *cmd, t_mini *mini, int *pipefd);
int		str_return(char *str, int exit_status, t_mini *mini);

#endif
