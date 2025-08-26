/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:00 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/26 18:32:54 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

#include <stdbool.h>

// typedef struct s_env
// {
// 	char			*var;
// 	struct s_env	*next;
// }t_env;

typedef struct s_token
{
	char			*content;
	int 			type;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	char			*filename;
	int				type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	char			**paths;
	t_redir			*infiles;
	t_redir			*outfiles;
	// int				dup_std[2];
	int				type;
	char			*pathname;
	char			*expend;
	int				nb_agrs;
	int				outpipe;
	int				fd_infile; //initialiser a STDIN si pas de redirection
	int				fd_outfile; //initialiser a STDOUT si pas de redirection
	int				quote; //1 si c'est single quote | 2 si c'est double | 0 s'il y en a pas
	int				error;
	// int				pid;
	bool			valid;
	bool			is_env_var; //si c'est une variable d'environnement.
	bool			malloc_error;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_gmalloc
{
	void				*memory;
	struct s_gmalloc	*next;
}t_gmalloc;

typedef struct s_input
{
	int		i;
	int		index;
	int		count;
	int		sq;
	int		dq;
}t_input;

typedef struct s_mini
{
	t_cmd		*cmd;
	t_token		*token;
	t_gmalloc	*gmalloc;
	int			dup_std[2];
	int			nb_pipe;
	int			exit_status;
	char		**env;
}t_mini;

typedef struct s_sort
{
	int	i;
	int	j;
	int	j_min;
	int	len;
}t_sort;

#endif