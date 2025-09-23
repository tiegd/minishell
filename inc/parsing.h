/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:54:07 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/23 14:23:04 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"

/*----------PARSING----------*/

int		ft_parsing(char *input, t_mini *mini);
char	**multi_split(char *s, t_gmalloc **head);
int		open_for_each_cmd(t_cmd **head, t_mini *mini);
char	*handle_env_var(char *prompt, t_mini *mini);

/*----------token------------*/

t_cmd	*init_cmd(t_token **token, t_gmalloc **head);
t_token	*handle_quote(t_token **token);
char	**ft_add_cmd(char **paths, int nb_path, t_cmd *cmd, t_gmalloc **head);
int		ft_nb_path(char **path);
char	**env_dash_i(t_gmalloc **head);
int		count_here_doc(t_token **head, t_gmalloc **gb_head);
int		is_alone(char **isolated, int i);

/*--------IDENTIFIERS------*/

int		is_quote(char c);
int		is_dq(char c);
int		is_sq(char c);
int		is_append(char c, char d);
int		is_here_doc(char c, char d);
int		is_special(char c);
int		is_ws(char c);
int		exp_isalnum(int c);
int		exp_isalnum_question_mark(int c);
int		is_redir(char c);
int		is_eof(char	*prev);
int		is_operator(char c);

/*-------SYNTAXE ERROR-----*/

int		syntax_error(char *prompt);
int		skip_ws_isalnum(char *prompt);
void	skip_quotes(char *prompt, int	*i, int quote);
int		operator_syntax_error(char *prompt, int *i);
int		redir_syntax_error(char *prompt, int *i);
int		not_required(char c);

#endif
