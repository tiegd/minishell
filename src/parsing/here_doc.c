/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:46:47 by jpiquet           #+#    #+#             */
/*   Updated: 2025/07/28 09:57:50 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_rand_name_file(t_gmalloc **head)
{
	char	urand[6];
	char	*file_name;
	int		fd;
	int		i;

	i = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, urand, 6) == -1)
		return (NULL);
	close(fd);
	while (i < 6)
	{
		urand[i] = '0' + (urand[i] % 10);
		i++;
	}
	file_name = gb_strjoin_custom("sh-thd-", urand, head);
	printf("urand = %s\n", urand);
	return (file_name);
	// urand = get_next_line()
}

int	create_here_doc(t_mini *mini, t_gmalloc **head)
{
	int		fd;
	char	*file_name;
	(void)mini;

	file_name = generate_rand_name_file(head);
	// printf("file_name = %s\n", file_name);
	// if (file_name == NULL)
	// 	return (-1);
	// fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if ((fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0664)) == -1)
		return (-1);
	// mini->cmd->
	return (fd);
}

int		here_doc(t_mini *mini, char *eof, t_gmalloc **head)
{
	char	*line;
	int		here_doc;

	// here_doc = create_here_doc(mini, head);
	if ((here_doc = create_here_doc(mini, head)) == -1)
		return (-1);
	// if (dup2(here_doc, STDIN_FILENO) == -1)
		// return (1);
	while ((line = readline(">")) != NULL)
	{
		if (ft_strcmp(line, eof))
			break ;
		if (ft_strchr(eof, DQ) || ft_strchr (eof, SQ))
		
		ft_putchar_fd('\n', here_doc);
		ft_putstr_fd(line, here_doc);
	}
	// if (dup2(here_doc, STDIN_FILENO) == -1)
	// 	return (1);
	return (here_doc);
}
