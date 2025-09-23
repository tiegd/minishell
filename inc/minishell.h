/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:59:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 14:51:56 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "struct.h"
# include <sys/wait.h>

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

extern volatile int	g_sig_flag;

/*-----added-----------*/

void	print_error_here_doc(char *eof, t_mini *mini);

/*--------SIGNALS-----------*/

void	handle_sig(int sig);
void	block_sig_int(void);
void	set_sig_action(void);
void	unblock_sig_quit(void);
void	block_sig_quit(void);

/*--------HERE_DOC----------*/

int		create_here_doc(t_mini *mini, char *eof, t_gmalloc **head);
char	*handle_env_var_for_here_doc(char *prompt, t_mini *mini);
char	*generate_rand_name_file(t_gmalloc **head);

/*--------HANDLE-LIST----------*/

t_token	*tab_to_lst(char **prompt, t_gmalloc **head);

/*--------UTILS----------*/

int		count_args(t_token	*token);
int		ft_strcmp(char *s1, char *s2);

/*-for multi_split-*/

int		extract_token(char **double_tab, char *s,
			t_input *in, t_gmalloc **head);
int		handle_special_char(char **double_tab, char *s,
			t_input *in, t_gmalloc **head);
int		check_empty_s(const char *s, char c, char d);
char	*delete_quote(char *str);
void	init_index(t_input *in);
void	skip_special_char(char *s, t_input *in);
void	skip_white_space(char *s, t_input *in);
int		skip_and_check_quotes(int *i, char *prev);

/*---random--------*/

int		count_tab(char **tab);

#endif