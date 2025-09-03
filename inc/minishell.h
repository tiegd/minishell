/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:59:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/03 10:39:41 by jpiquet          ###   ########.fr       */
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
#include <sys/wait.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

/*---------TOKEN---------*/

#define SQ 39
#define DQ 34
#define BS 92

enum e_types
{
	TRUE,
	FALSE,
	INPUT,
	OUTPUT,
	APPEND,
	HERE_DOC,
	PIPE,
	ARGS,
	VAR,
	PATH,
};

extern int	sig_flag;
/*----------PARSING----------*/

int 	ft_parsing(char *input, t_mini *mini);
int		syntax_error(char *prompt);
int 	char_not_required(char *prompt);
// int		ft_check_prompt(char *input);
char	**ft_multi_split(char *s, t_gmalloc **head);
int		ft_count_word(char *s);
// t_token	*ft_tab_to_lst(char **prompt, int len_tab);
t_cmd	*ft_init_cmd(t_token *token, t_gmalloc **head);
int		ft_strcmp(char *s1, char *s2);
t_token *ft_handle_quote(t_token *token);
char	*handle_env_var(char *prompt, t_mini *mini);
// void	ft_lstfree(t_token *lst);
// bool	ft_first_word(t_token *lst);
int		ft_is_bin(t_cmd *cmd, t_mini *mini);
char	**ft_add_cmd(char **paths, int nb_path, t_cmd *cmd, t_gmalloc **head);
char	*ft_add_suf(int j, char *str, char *args);
int	    ft_count_path(char *paths);
bool	ft_is_pipe(t_token *lst);
// void	define_type(t_token *lst);
char	*ft_path_line(char **env, t_gmalloc **head);
int		ft_nb_path(char **path);
char	**env_dash_i(t_gmalloc **head);

/*--------SIGNALS-----------*/

void	handle_sig(int sig);
void	set_sig_action(void);
void	unblock_sig_quit(void);
void	block_sig_quit(void);

/*--------HERE_DOC----------*/

int		here_doc(t_mini *mini, char *eof, t_gmalloc **head);
char	*handle_env_var_for_here_doc(char *prompt, t_mini *mini);

/*--------HANDLE-LIST----------*/

t_token	*ft_lst_last(t_token *lst);
t_token	*ft_lst_addback(t_token *lst, char *s, int len, t_gmalloc **head);
t_token	*ft_tab_to_lst(char **prompt, int len_tab, t_gmalloc **head);
void	ft_print_lst(t_token *lst);
char	*lexing_input(char *input);
int		is_ws(char c);

/*--------UTILS----------*/

/*-for multi_split-*/

int		extract_token(char **double_tab, char *s, t_input *in, t_gmalloc **head);
int		handle_special_char(char **double_tab, char *s, t_input *in, t_gmalloc **head);
int		check_empty_s(const char *s, char c, char d);
void	update_quotes(char c, int *sq, int *dq);
char	*delete_quote(char *str);
void	init_index(t_input *in);
void	skip_special_char(char *s, t_input *in);
void	skip_white_space(char *s, t_input *in);
void	skip_alpha(char *s, int *sq, int *dq, int *i);
void	skip_beetwen_quotes(char *s, int *i, int *sq, int *dq);

/*--garbage_collector_lib--*/

char	*gb_substr(char const *s, unsigned int start, size_t len, t_gmalloc **head);
char	*gb_strdup(const char *s, t_gmalloc **gmalloc);
char	*gb_strjoin_custom(char *s1, char *s2, t_gmalloc **head);
char	*gb_itoa(int nb, t_gmalloc **head);
char	**gb_split(char const *s, char c, t_gmalloc **head);

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
int		exp_isalnum_question_mark(int c);
int		is_redir(char c);

/*--------BUILT-IN--------*/

void	ft_echo(t_cmd *cmd);
void	ft_env(char **env, int fd);
char	**ft_export(char **old_env, char *str, t_mini *mini, t_gmalloc **head);
void	pwd(int fd, t_mini *mini);
void	cd(char	**args, char **env, t_gmalloc **head, t_mini *mini);
char	**unset(char *var, char **old_env, t_gmalloc **head);
char	**loop_unset(char **env, char **args, t_gmalloc **head);
char	*expend(char *arg, char **env, t_gmalloc **head, t_mini *mini);
char	**loop_export(char **env, char **args, t_mini *mini, t_gmalloc **head);
void	ft_exit(char **args, t_mini *mini, t_gmalloc **head);
void	print_export(char **env, t_gmalloc **head);

/*--------BUILT-IN_UTILS--------*/

/*--------FREE(S)--------*/

char	**free_split(char **double_tab, int nb_word, t_gmalloc **head);
int		nb_var(char **env);
int		strcmp_until_char(char *s1, char *s2, char c);

/*--------EXEC--------*/

int	    is_builtin(char *content);
int		ft_exec_builtin(t_cmd *cmd, t_mini *mini, t_gmalloc **head);
bool	ft_exec_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head);
void	ft_one_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head);
void    manage_error_exec(t_cmd *cmd, t_mini *mini); //, char **paths);
int 	extract_path(t_cmd *cmd, t_mini *mini, t_gmalloc **head);
void	put_exit_error(t_mini *mini, char *filename, char *error, int exit_status);
void	put_error(t_mini *mini, char *filename, char *error, int exit_status);
int		check_cmd(t_cmd *cmd, t_mini *mini, t_gmalloc **head);

/*------------PIPEX------------*/

void	pipex(t_cmd *cmd, t_mini *mini, int nb_pipe, t_gmalloc **head);
int		ft_count_pipe(t_token **token);
void    wait_children(pid_t pid_last, t_mini *mini);

/*--------GARBAGE_COLLECTOR----*/

void	*gb_malloc(size_t size, t_gmalloc **lst);
void	gmalloc_add_back(t_gmalloc **head, t_gmalloc *new);
void	gfree(void *ptr, t_gmalloc **head);
void	gb_free_all(t_gmalloc **head);
// t_gmalloc	*gmalloc_last(t_gmalloc *lst);

/*------------CLEAN------------*/

void	close_fds(int infile, int outfile);
void	free_token(t_token *lst, t_gmalloc **head);
void	free_redir(t_redir *redir, t_gmalloc **head);
char	**free_double_tab(char **tab, int nb_agrs, t_gmalloc **head);
void	free_cmd(t_cmd *cmd, t_gmalloc **head);
void	ft_lstfree(t_token *lst, t_gmalloc **head);
void	print_not_valid_identifier(char *str);
void	print_no_such_file(char *str);
void	print_error_exit_arg(char *str);

/*------------FD------------*/

void	ft_init_fd(t_token *lst);
int		ft_open_fd(t_cmd *cmd, t_mini *mini);
int		ft_open_infile(t_cmd *cmd, t_mini *mini);
void	ft_open_outfile(t_cmd *cmd);
int	    ft_close_fd(t_cmd *cmd, int *pipefd);
// void	ft_fd_to_pipe(t_cmd *cmd);
void	ft_fd_to_pipe(t_mini *mini);
void	ft_dup_out(t_mini *mini);

/*------------EXIT------------*/

// void	exit_pid_error(int *pipefd, t_cmd *cmd);
void	exit_pid_error(int *pipefd, t_mini *mini);
// void	exit_tab(t_cmd *cmd, int code);
void	exit_tab(t_mini *mini, int code, int *pipefd);
// void	exit_fd(int fd, t_cmd *cmd);
void	exit_fd(t_cmd *cmd, t_mini *mini, int *pipefd);
int		str_return(const char *str, int exit_status, t_mini *mini);

/*------------TEST------------*/

void	ft_print_lst(t_token *lst);
void	ft_print_cmd(t_cmd *lst);
void	print_tab_char(char **tab);
void	ft_print_tab(char **path, int nb_path);
void	print_tab_int(int *tab);
void	ft_print_redir(t_redir *lst);
void	ft_print_memory(t_gmalloc *lst);

#endif