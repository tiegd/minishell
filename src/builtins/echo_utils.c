/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:39:59 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/23 10:49:07 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gblib.h"
#include "builtins.h"
#include "libft.h"

void	print_with_new_line(char *s, t_gmalloc **head)
{
	char	*s_new;

	s_new = gb_strjoin_custom(s, "\n", head);
	ft_putstr_fd(s_new, 1);
}

void	print_with_space(char *s, t_gmalloc **head)
{
	char	*s_new;

	s_new = gb_strjoin_custom(s, " ", head);
	ft_putstr_fd(s_new, 1);
}
