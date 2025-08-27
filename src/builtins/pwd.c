/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:06:08 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/27 18:34:22 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*print le path dans lequel on se situe actuellement*/
void	pwd(int fd, t_mini *mini)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n", 2);
		mini->exit_status = 1;
		return ;
	}
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
	free(pwd);
}