/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:54:11 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/09 16:20:05 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"
# include <stdlib.h>

/*--------FREE(S)--------*/

char	**free_split(char **double_tab, int nb_word, t_gmalloc **head);
int		nb_var(char **env);
int		strcmp_until_char(char *s1, char *s2, char c);
int		env_var_cmp(char *s1, char *s2);

/*--------EXEC--------*/

int		is_builtin(char *content);
int		ft_exec_builtin(t_cmd *cmd, t_mini *mini, t_gmalloc **head);
bool	ft_exec_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head, int pid);
void	ft_one_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head);
int		manage_error_exec(t_cmd *cmd, t_mini *mini); //, char **paths);
int		extract_path(t_cmd *cmd, t_mini *mini, t_gmalloc **head);
void	put_exit_error(t_mini *mini, char *filename,
			char *error, int exit_status);
void	put_error(t_mini *mini, char *filename, char *error, int exit_status);
int		check_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head);
void	one_no_fork(t_cmd *cmd, t_mini *mini, t_gmalloc **head);

/*------------PIPEX------------*/

void	pipex(t_cmd *cmd, t_mini *mini, t_gmalloc **head);
int		count_pipe(t_token **token);
void	wait_children(pid_t pid_last, t_mini *mini);

#endif
