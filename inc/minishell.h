/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:59:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/08 18:16:39 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <limits.h>
# include <fcntl.h>
# include "libft.h"
# include "struct.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define RESET   "\033[0m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"

/*---------TOKEN---------*/

# define SQ 39
# define DQ 34
# define BS 92

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

extern int	g_sig_flag;

/*----------PARSING----------*/

int		ft_parsing(char *input, t_mini *mini);
char	**multi_split(char *s, t_gmalloc **head);

/*----------token------------*/

t_cmd	*init_cmd(t_token **token, t_gmalloc **head);
t_token	*handle_quote(t_token **token);
char	*handle_env_var(char *prompt, t_mini *mini);
int		ft_is_bin(t_cmd *cmd, t_mini *mini);
char	**ft_add_cmd(char **paths, int nb_path, t_cmd *cmd, t_gmalloc **head);
char	*ft_add_suf(int j, char *str, char *args);
char	*ft_path_line(char **env, t_gmalloc **head);
int		ft_nb_path(char **path);
char	**env_dash_i(t_gmalloc **head);

/*--------SIGNALS-----------*/

void	handle_sig(int sig);
void	set_sig_action(void);
void	unblock_sig_quit(void);
void	block_sig_quit(void);

/*--------HERE_DOC----------*/

int		create_here_doc(t_mini *mini, char *eof, t_gmalloc **head);
char	*handle_env_var_for_here_doc(char *prompt, t_mini *mini);
char	*generate_rand_name_file(t_gmalloc **head);

/*--------HANDLE-LIST----------*/

t_token	*ft_lst_last(t_token *lst);
t_token	*ft_lst_addback(t_token *lst, char *s, int len, t_gmalloc **head);
t_token	*tab_to_lst(char **prompt, t_gmalloc **head);
char	*lexing_input(char *input);
int		is_ws(char c);

/*--------UTILS----------*/

int		count_args(t_token	*token);
int		ft_strcmp(char *s1, char *s2);

/*-for multi_split-*/

int		extract_token(char **double_tab, char *s,
			t_input *in, t_gmalloc **head);
int		handle_special_char(char **double_tab, char *s,
			t_input *in, t_gmalloc **head);
int		check_empty_s(const char *s, char c, char d);
void	update_quotes(char c, int *sq, int *dq);
char	*delete_quote(char *str);
void	init_index(t_input *in);
void	skip_special_char(char *s, t_input *in);
void	skip_white_space(char *s, t_input *in);
void	skip_alpha(char *s, int *sq, int *dq, int *i);
void	skip_beetwen_quotes(char *s, int *i, int *sq, int *dq);
int		skip_and_check_quotes(int *i, char *prev);

/*--garbage_collector_lib--*/

char	*gb_substr(char const *s, unsigned int start,
			size_t len, t_gmalloc **head);
char	*gb_strdup(char *s, t_gmalloc **gmalloc);
char	*gb_strjoin_custom(char *s1, char *s2, t_gmalloc **head);
char	*gb_itoa(int nb, t_gmalloc **head);
char	**gb_split(char *s, char c, t_gmalloc **head);
char	*gb_strjoin(char *s1, char *s2, t_gmalloc **head);

/*---random--------*/

int		count_tab(char **tab);

/*-------SYNTAXE ERROR-----*/

int		syntax_error(char *prompt);
int		skip_ws_isalnum(char *prompt);
void	skip_quotes(char *prompt, int	*i, int quote);
int		operator_syntax_error(char *prompt, int *i);
int		redir_syntax_error(char *prompt, int *i);
int		not_required(char c);

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

/*--------BUILT-IN--------*/

void	ft_echo(t_cmd *cmd);
void	ft_env(char **env, int fd, t_mini *mini);
char	**ft_export(char **old_env, char *str, t_mini *mini, t_gmalloc **head);
void	pwd(int fd, t_mini *mini);
void	cd(char	**args, t_gmalloc **head, t_mini *mini);
char	**unset(char *var, char **env, t_gmalloc **head);
char	**loop_unset(char **env, char **args, t_mini *mini, t_gmalloc **head);
char	*expend(char *arg, char **env, t_gmalloc **head, t_mini *mini);
char	**loop_export(char **env, char **args, t_mini *mini, t_gmalloc **head);
void	ft_exit(char **args, t_mini *mini, t_gmalloc **head);
void	print_export(char **env, t_mini *mini, t_gmalloc **head);

/*--------BUILT-IN_UTILS--------*/

/*expend utils*/

int		strcmp_until_char(char *s1, char *s2, char c);
char	*add_double_quote(char *res, t_gmalloc **head);
int		has_special(char *str);
char	*env_result(char *env, t_gmalloc **head);
int		count_size(int n);
int		which_quote(char *prompt, int *index);
char	**split_parts(char *prompt, t_gmalloc **head);

/*export utils*/

int		env_var_cmp(char *s1, char *s2);
int		is_valid_identifier(char *variable, t_mini *mini);
int		is_empty_var(char *variable);
void	replace_same_var(char *new_var, char **new_env,
			int i, t_gmalloc **head);
int		handle_same_var(char *new_var, char **new_env, int i, t_gmalloc **head);

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

/*------------REDIR------------*/

void	redir_first_pipe(t_mini *mini, t_cmd *cmd, int *pipefd);
void	redir_middle_pipe(t_mini *mini, t_cmd *cmd, int *pipefd);
void	redir_last_pipe(t_mini *mini, t_cmd *cmd, int *pipefd);
void	redir_one(t_cmd *cmd, t_mini *mini);

/*--------GARBAGE_COLLECTOR----*/

void	*gb_malloc(size_t size, t_gmalloc **lst);
void	gmalloc_add_back(t_gmalloc **head, t_gmalloc *new);
void	gfree(void *ptr, t_gmalloc **head);
void	gb_free_all(t_gmalloc **head);
char	*gb_itoa(int nb, t_gmalloc **head);

/*------------CLEAN------------*/

void	free_token(t_token *lst, t_gmalloc **head);
void	free_redir(t_redir *redir, t_gmalloc **head);
char	**free_double_tab(char **tab, int nb_agrs, t_gmalloc **head);
void	free_cmd(t_cmd *cmd, t_gmalloc **head);
void	print_not_valid_identifier(char *str);
void	print_no_such_file(char *str);
void	print_error_exit_arg(char *str);
char	**free_prompt(char **double_tab, t_gmalloc **head);
void	free_one_cmd(t_cmd *cmd, t_gmalloc **head);

/*------------FD------------*/

int		ft_open_fd(t_cmd *cmd, t_mini *mini);
int		ft_close_fd(t_cmd *cmd, int *pipefd);
void	close_fds(int infile, int outfile);
void	ft_dup_out(t_mini *mini);

/*------------EXIT------------*/

void	exit_pid_error(int *pipefd, t_mini *mini);
void	exit_tab(t_cmd *cmd, t_mini *mini, int code, int *pipefd);
void	exit_fd(t_cmd *cmd, t_mini *mini, int *pipefd);
int		str_return(char *str, int exit_status, t_mini *mini);

/*------------TEST------------*/

void	ft_print_lst(t_token *lst);
void	ft_print_cmd(t_cmd *lst);
void	print_tab_char(char **tab);
void	ft_print_tab(char **path, int nb_path);
void	print_tab_int(int *tab);
void	ft_print_redir(t_redir *lst);
void	ft_print_memory(t_gmalloc *lst);

#endif