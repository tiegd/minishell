/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:59:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/05/26 18:30:13 by jpiquet          ###   ########.fr       */
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

void	ft_echo(t_cmd *cmd);
int		ft_strcmp(char *s1, char *s2);
void	ft_env(char **env, int fd);
char	*expend(char *arg, char **env, bool malloc_error);
char	**ft_export(char **old_env, char *str);

#endif