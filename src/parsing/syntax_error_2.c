/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 09:14:15 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 08:38:50 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Liste des caractères qu'on ne doit pas traiter :  ( ) \ & *   */

int	not_required(char c)
{
	if (c == '(')
		return (1);
	if (c == ')')
		return (1);
	if (c == BS)
		return (1);
	if (c == '&')
		return (1);
	if (c == '*')
		return (1);
	return (0);
}

/*skip all the white space and the alpha numeric character*/

int	skip_ws_isalnum(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && (is_ws(prompt[i]) || exp_isalnum(prompt[i])))
		i++;
	return (i);
}

void	skip_quotes(char *prompt, int	*i, int quote)
{
	(*i)++;
	while (prompt[*i] && prompt[*i] != quote)
	{
		(*i)++;
	}
	if (prompt[*i] == quote)
		(*i)++;
}

int	operator_syntax_error(char *prompt, int *i)
{
	(*i)++;
	while (prompt[*i] && is_ws(prompt[*i]))
		(*i)++;
	if (is_operator(prompt[*i]) || prompt[*i] == '\0' || prompt[*i] == '\n')
		return (1);
	return (0);
}

int	redir_syntax_error(char *prompt, int *i)
{
	if (is_append(prompt[*i], prompt[*i + 1])
		|| is_here_doc(prompt[*i], prompt[*i + 1]))
		(*i) += 2;
	else
		(*i)++;
	while (prompt[*i] && is_ws(prompt[*i]))
		(*i)++;
	if (is_operator(prompt[*i]) || prompt[*i] == '\0'
		|| prompt[*i] == '\n' || is_redir(prompt[*i]))
		return (1);
	return (0);
}
