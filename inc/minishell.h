/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:59:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/10 14:54:29 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include "../Libft/libft.h"
#include "struct.h"

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

/*---------TOKEN---------*/

#define	CMD 10			//	cat ls grep etc..
#define	VAR 20			//	$SOMETHING
#define	PIPE 30			//	|
#define	INPUT 40		//	<
#define	OUTPUT 50		//	>
#define	APPEND 60		//	>>
#define	HERE_DOC 70		//	<<
#define PATH 80 		//	path/
#define ARGS 90			//	something
#define BUILTIN 100		//	cd pwd env etc..
#define FD 110			//	file after <, >, >>.

/*----------PARSING----------*/

char	**ft_multi_split(char const *s, char c, char d);
int		ft_check_prompt(char *input);
int		ft_count_word(const char *s, char c, char d);
t_token	*ft_tab_to_lst(char **prompt, int len_tab);
bool 	ft_parsing(char *input, char **env);

/*----------UTILS-------------*/

int		nb_var(char **env);
int		strcmp_until_char(char *s1, char *s2, char c);
char	**envdup(char **old_env);
char	**env_dash_i(void);

/*----------BUILT-IN----------*/

void	ft_echo(t_cmd *cmd);
int		ft_strcmp(char *s1, char *s2);
void	ft_env(char **env, int fd);
char	**ft_export(char **old_env, char *str);
void	pwd(int fd);
void	cd(char	**args, char **env, bool malloc_error);
char	**unset(char *var, char **old_env);
char	*expend(char *arg, char **env, bool malloc_error);

/*------------PIPEX------------*/

void	pipex(t_token *lst, t_cmd *cmd, char **env);

#endif