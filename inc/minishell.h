/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:59:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/04 16:27:18 by jpiquet          ###   ########.fr       */
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