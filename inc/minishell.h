/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:59:49 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/13 13:49:06 by jpiquet          ###   ########.fr       */
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
	PATH
};



/*--------FUNCTION-------*/

char	**ft_multi_split(char const *s);
// int		ft_check_prompt(char *input);
int		ft_count_word(const char *s);
t_token	*ft_tab_to_lst(char **prompt, int len_tab);
int 	ft_parsing(char *input, char **env);
t_cmd	*ft_init_cmd(t_token *token);
int		ft_strcmp(char *s1, char *s2);
t_token *ft_handle_quote(t_token *token);

/*--------UTILS----------*/

int		is_quote(char c);

void	ft_echo(t_cmd *cmd);
void	ft_env(char **env, int fd);
char	*expend(char *arg, char **env);


/*-----------HELP--------------------*/

void	ft_print_lst(t_token *lst);
void	ft_print_cmd(t_cmd *lst);

#endif