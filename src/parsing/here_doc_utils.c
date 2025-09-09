/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:58:58 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/09 09:51:15 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <dirent.h>

static int	dir_is_valid(const char *dirname)
{
	DIR	*dir;

	dir = opendir(dirname);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	else
		return (0);
}

char	*generate_rand_name_file(t_gmalloc **head)
{
	unsigned char	urand[7];
	char			*file_name;
	int				fd;
	int				i;

	i = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, urand, 6) == -1)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	while (i < 6)
	{
		urand[i] = '0' + (urand[i] % 10);
		i++;
	}
	urand[i] = '\0';
	file_name = gb_strjoin_custom("sh-thd-", (char *)urand, head);
	if (dir_is_valid("/tmp"))
		file_name = gb_strjoin_custom("/tmp/", file_name, head);
	return (file_name);
}
