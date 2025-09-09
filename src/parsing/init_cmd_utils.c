/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:35:07 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/08 13:45:36 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token	*token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == APPEND || token->type == HERE_DOC
			|| token->type == INPUT || token->type == OUTPUT)
			token = token->next->next;
		else if (token && token->type == PIPE)
			token = token->next;
		else if (token)
		{
			count++;
			token = token->next;
		}
		else
			break ;
	}
	return (count);
}
