/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:59:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/27 17:01:25 by gaducurt         ###   ########.fr       */
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

char	**ft_multi_split(char const *s, char c, char d);
int		ft_check_prompt(char *input);
int		ft_count_word(const char *s, char c, char d);
t_cmd	*ft_tab_to_lst(t_cmd *lst, char **prompt, int len_tab);
int 	ft_parsing(char *input);

void	ft_echo(t_cmd *cmd);
int		ft_strcmp(char *s1, char *s2);
void	ft_env(char **env, int fd);
char	*expend(char *arg, char **env);

#endif