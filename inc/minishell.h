/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:59:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/03 09:51:47 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <fcntl.h>
#include "../Libft/libft.h"
#include "struct.h"
#include <readline/readline.h>
#include <readline/history.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

/*---------TOKEN---------*/

// #define	CMD 10			//	cat ls grep etc..
// #define	VAR 20 			//	$SOMETHING
// #define	PIPE 30 		//	|
// #define	INPUT 40 		//	<
// #define	OUTPUT 50 		//	>
// #define	APPEND 60		//	>>
// #define	HERE_DOC 70		//	<<
// #define PATH 80 			//	path/
// #define ARGS 90			//	something
// #define BUILTIN 100		//	cd pwd env etc..

#define SQ 39
#define DQ 34

enum e_types
{
	INPUT,
	OUTPUT,
	APPEND,
	HERE_DOC,
	PIPE,
	ARGS,
	VAR,
	PATH,
};



/*----------PARSING----------*/
/*--------FUNCTION-------*/

// int		ft_check_prompt(char *input);
char	**ft_multi_split(char *s);
int		ft_count_word(char *s);
t_token	*ft_tab_to_lst(char **prompt, int len_tab);
t_cmd	*ft_init_cmd(t_token *token);
int		ft_strcmp(char *s1, char *s2);
t_token *ft_handle_quote(t_token *token);
char	*handle_env_var(char *prompt, char **env);
void	ft_lstfree(t_token *lst);
int 	ft_parsing(char *input, char **env, t_token *token);
bool	ft_first_word(t_token *lst);
char	*ft_is_bin(char **paths, int nb_path);
char	**ft_add_cmd(char **paths, int nb_path, t_cmd *cmd);
char	*ft_add_suf(int j, char *str, char *args);
int	    ft_count_path(char *paths);
bool	ft_is_pipe(t_token *lst);
bool	ft_exec_cmd(t_cmd *cmd, char **env);
int	    is_builtin(char *content);
void	define_type(t_token *lst);

/*--------HANDLE-LIST----------*/

t_token	*ft_lst_last(t_token *lst);
t_token	*ft_lst_addback(t_token *lst, char *s, int len);
t_token	*ft_tab_to_lst(char **prompt, int len_tab);
void	ft_print_lst(t_token *lst);

char	*lexing_input(char *input);
int		is_ws(char c);

/*--------UTILS----------*/

/*-for multi_split-*/

int		extract_token(char **double_tab, char *s, t_input *in);
int		handle_special_char(char **double_tab, char *s, t_input *in);
int		check_empty_s(const char *s, char c, char d);

void	update_quotes(char c, int *sq, int *dq);
void	init_index(t_input *in);
void	skip_special_char(char *s, t_input *in);
void	skip_white_space(char *s, t_input *in);
void	skip_alpha(char *s, int *sq, int *dq, int *i);
void	skip_beetwen_quotes(char *s, int *i, int *sq, int *dq);

/*---random--------*/

int	count_tab(char **tab);

/*--------IDENTIFIERS------*/

int		is_quote(char c);
int		is_dq(char c);
int		is_sq(char c);
int		is_append(char c, char d);
int		is_here_doc(char c, char d);
int		is_special(char c);
int		is_ws(char c);
int		exp_isalnum(int c);

/*--------BUILT-IN--------*/

void	ft_echo(t_cmd *cmd);
void	ft_env(char **env, int fd);
char	**ft_export(char **old_env, char *str);
void	pwd(int fd);
void	cd(char	**args, char **env, bool malloc_error);
char	**unset(char *var, char **old_env);
char	*expend(char *arg, char **env, bool malloc_error);

/*--------BUILT-IN_UTILS--------*/
/*--------FREE(S)--------*/

char	**free_split(char **double_tab, int nb_word);

int	nb_var(char **env);
int		strcmp_until_char(char *s1, char *s2, char c);

/*------------PIPEX------------*/

void	pipex(t_cmd *cmd, char *env[], int nb_pipe, t_token *lst);

/*------------CLEAN------------*/

void	free_token(t_token *lst);
void	free_redir(t_redir *redir);
char	**free_double_tab(char **tab, int nb_agrs);
void	free_cmd(t_cmd *cmd);
void	free_struct(t_cmd *cmd, t_token *lst);
void	ft_lstfree(t_token *lst);

/*------------FD------------*/

void	ft_init_fd(t_token *lst);
int 	ft_open_fd(t_cmd *cmd);
int	    ft_close_fd(t_cmd *cmd, int *pipefd);

/*------------EXIT------------*/

void	exit_pid_error(int *pipefd, t_cmd *cmd, t_token *lst);
void	exit_tab(t_cmd *cmd, t_token *lst, int code);
void	exit_fd(int fd, t_cmd *cmd, t_token *lst);

/*------------TEST------------*/

void	ft_print_tab(char **path, int nb_path);
void	ft_print_lst(t_token *lst);
void	ft_print_cmd(t_cmd *lst);
void	print_tab_char(char **tab);
void	ft_print_tab(char **path, int nb_path);
void	print_tab_int(int *tab);
void	ft_print_redir(t_redir *lst);

#endif