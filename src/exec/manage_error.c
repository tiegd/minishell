/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:46:16 by gaducurt          #+#    #+#             */
/*   Updated: 2025/09/23 14:20:41 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "clean.h"
#include "gblib.h"
#include <sys/stat.h>

void	put_error(t_mini *mini, char *filename, char *error, int exit_status)
{
	char	*str;

	str = gb_strjoin_custom("minishell: ", filename, &mini->gmalloc);
	str = gb_strjoin_custom(str, ": ", &mini->gmalloc);
	str = gb_strjoin_custom(str, error, &mini->gmalloc);
	str = gb_strjoin_custom(str, "\n", &mini->gmalloc);
	ft_putstr_fd(str, 2);
	mini->exit_status = exit_status;
}

int	manage_error_exec(t_cmd *cmd, t_mini *mini)
{
	struct stat	buf;

	if (!cmd->args[0] || cmd->args[0][0] == '\0')
		return (0);
	if ((cmd->args[0][0] == '~' && cmd->args[0][1] == '\0')
		|| cmd->args[0][1] == '+' || cmd->args[0][1] == '-')
	{
		put_error(mini, cmd->paths[0], "Is a directory", 126);
		return (1);
	}
	if (cmd->args[0][0] == '.' && cmd->args[0][1] == '\0')
	{
		put_error(mini, cmd->args[0], "filename argument required", 2);
		return (1);
	}
	else if (stat(cmd->args[0], &buf) == 0 && ft_strchr(cmd->args[0], '/'))
	{
		if (S_ISDIR(buf.st_mode))
		{
			put_error(mini, cmd->args[0], "Is a directory", 126);
			return (1);
		}
	}
	return (0);
}
