/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerzone <amerzone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:13:31 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/05 16:06:39 by amerzone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_append(char c, char d)
{
	if (c == '>' && d == '>')
		return (1);
	return (0);
}

int	is_here_doc(char c, char d)
{
	if (c == '<' && d == '<')
		return (1);
	return (0);
}

int	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

/*isalnum où le '_' est autorisé*/

int	exp_isalnum(int c) 
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	else
		return (0);
}

int	exp_isalnum_question_mark(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_' || c == '?')
		return (1);
	else
		return (0);
}
