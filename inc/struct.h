/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:00 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/11 10:52:02 by jpiquet          ###   ########.fr       */
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
}t_redir;


typedef struct s_cmd
{
	char			**args;
	// char			*expend;
	int				infile; //initialiser a STDIN si pas de redirection
	int				outfile; //initialiser a STDOUT si pas de redirection
	int				quote; //1 si c'est single quote | 2 si c'est double | 0 s'il y en a pas
	bool			valid;
	bool			is_env_var; //si c'est une variable d'environnement.
	bool			malloc_error;
	struct s_cmd	*next;
}t_cmd;

#endif