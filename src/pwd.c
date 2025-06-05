/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:06:08 by jpiquet           #+#    #+#             */
/*   Updated: 2025/06/04 13:24:25 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*print le path dans lequel on se situe actuellement*/
void	pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("error with getcwd");
		return ;
	}
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
	free(pwd);
}