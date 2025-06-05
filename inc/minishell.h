/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:59:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/05 10:30:21 by gaducurt         ###   ########.fr       */
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

char	**ft_multi_split(char const *s, char c, char d);
int		ft_check_prompt(char *input);
int		ft_count_word(const char *s, char c, char d);
t_token	*ft_tab_to_lst(char **prompt, int len_tab);
int 	ft_parsing(char *input, char **env);

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

#endif