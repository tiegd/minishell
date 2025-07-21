/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:46:47 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/21 16:34:42 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_rand_name_file(t_gmalloc **head)
{
	char	urand[6];
	char	*file_name;
	int		fd;

	if (fd = open("/dev/urand", O_RDONLY) == -1)
		return (1);
	read(fd, urand, 6);
	file_name = gb_strjoin_custom("sh-thd-", urand, head);
	printf("urand = %s\n", urand);
	return (file_name);
	// urand = get_next_line()
}

int	create_here_doc(t_gmalloc **head)
{
	int		fd;
	char	*file_name;

	file_name = generate_rand_name_file(head);
	if (fd = open(file_name, O_CREAT, O_WRONLY) == -1)
		return (-1);
	return (fd);
}

int		here_doc(char *eof, t_gmalloc **head)
{
	char	*line;
	int		here_doc;

	if (here_doc = create_here_doc(head) == -1)
		return (-1);
	// if (dup2(here_doc, STDIN_FILENO) == -1)
	// 	return (1);
	while (line = readline("HERE_DOC>") != NULL)
	{
		if (ft_strcmp(line, eof))
			break ;
		ft_putstr_fd(line, here_doc);
	}
	return (here_doc);
}
