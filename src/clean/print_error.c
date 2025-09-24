/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jpiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:24:43 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/24 18:53:41 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "gblib.h"
#include "fd.h"

void	print_not_valid_identifier(char *str, t_mini *mini)
{
	char	*s;

	s = gb_strjoin_custom("minishell: export: '", str, &mini->gmalloc);
	s = gb_strjoin_custom(s, "': not a valid identifier\n", &mini->gmalloc);
	ft_putstr_fd(s, 2);
}

void	print_error_exit_arg(char *str, t_gmalloc **head)
{
	char	*s;

	s = gb_strjoin_custom("minishell: ", str, head);
	s = gb_strjoin_custom(s, ": numeric argument required\n", head);
	ft_putstr_fd(s, 2);
}

void	exit_wrong_arg(char *args, t_mini *mini)
{
	close_both_fd(mini->dup_std[0], mini->dup_std[1]);
	print_error_exit_arg(args, &mini->gmalloc);
	gb_free_all(&mini->gmalloc);
	exit(2);
}

void	print_error_here_doc(char *eof, t_mini *mini)
{
	char	*s;

	s = gb_strjoin_custom("minishell: warning: \
delimited by end-of-file (wanted '", eof, &mini->gmalloc);
	s = gb_strjoin_custom(s, "')\n", &mini->gmalloc);
	ft_putstr_fd(s, 2);
}
