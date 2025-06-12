/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:00 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/12 15:51:16 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

#include <stdbool.h>

typedef struct s_token
{
	char			*content;
	int				index;
	int 			type;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	char	*filename;
	int		type;
	t_redir	*next;
}			t_redir;

// typedef struct	s_fd
// {
// 	int		infile;
// 	char	*path_in;
// 	int		outfile;
// 	char	*path_out;
// }			t_fd;

typedef struct s_cmd
{
	char			**args;
	t_redir			*infile;
	t_redir			*outfile;
	char			*pathname;
	// char			*expend;
	int				fd_infile; //initialiser a STDIN si pas de redirection
	int				fd_outfile; //initialiser a STDOUT si pas de redirection
	// t_fd			*fd;
	int				quote; //1 si c'est single quote | 2 si c'est double | 0 s'il y en a pas
	bool			valid;
	bool			is_env_var; //si c'est une variable d'environnement.
	bool			malloc_error;
	struct s_cmd	*next;
}					t_cmd;

#endif