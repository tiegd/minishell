/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:46:47 by jpiquet           #+#    #+#             */
/*   Updated: 2025/08/22 10:00:05 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_rand_name_file(t_gmalloc **head)
{
	unsigned char	urand[7];
	char	*file_name;
	int		fd;
	int		i;

	i = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
		return (NULL);
	if (read(fd, urand, 6) == -1)
		return (NULL);
	close(fd);
	while (i < 6)
	{
		urand[i] = '0' + (urand[i] % 10);
		i++;
	}
	urand[i] = '\0';
	file_name = gb_strjoin_custom("sh-thd-", (char *)urand, head);
	// file_name = gb_strjoin_custom("fd_here_doc/", file_name, head);
	return (file_name);
}

// int	create_here_doc(t_gmalloc **head)
// {
// 	int		fd;
// 	char	*file_name;
// 	file_name = generate_rand_name_file(head);
// 	// printf("file_name = %s\n", file_name);
// 	// if (file_name == NULL)
// 	// 	return (-1);
// 	// fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0664);
// 	file_name = gb_strjoin_custom("fd_here_doc/", file_name, head);
// 	if ((fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0664)) == -1)
// 		return (-1);
// 	// mini->cmd->
// 	return (fd);
// }

// char	*here_doc(t_mini *mini, char *eof, t_gmalloc **head)
// {
// 	char	*line;
// 	char	*file_name;
// 	int		here_doc;

// 	file_name = generate_rand_name_file(head);
// 	if ((here_doc = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0664)) == -1)
// 	{
// 		perror("error with open occured\n");
// 		return (NULL);
// 	}
// 	while ((line = readline(">")) != NULL)
// 	{
// 		if (ft_strcmp(line, eof))
// 			break ;
// 		if (ft_strchr(line, '$') && (ft_strchr(eof, DQ) || ft_strchr (eof, SQ)))
// 			line = handle_env_var_for_here_doc(line, mini);
// 		ft_putstr_fd(line, here_doc);
// 		ft_putchar_fd('\n', here_doc);
// 	}
// 	close(here_doc);
// 	return (file_name);
// }

int	here_doc(t_mini *mini, char *eof, t_gmalloc **head)
{
	char	*line;
	char	*file_name;
	int		here_doc;
	bool	had_quote;

	had_quote = false;
	file_name = generate_rand_name_file(head);
	printf("eof = %s\n", eof);
	if (ft_strchr(eof, DQ) || ft_strchr(eof, SQ))
	{
		had_quote = true;
		eof = delete_quote(eof);
	}
	if ((here_doc = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0664)) == -1)
		return (-1);
	while ((line = readline(">")) != NULL)
	{
		if (ft_strcmp(line, eof))
			break ;
		if (ft_strchr(line, '$') && had_quote == false)
			line = handle_env_var_for_here_doc(line, mini);
		ft_putstr_fd(line, here_doc);
		ft_putchar_fd('\n', here_doc);
	}
	if (close(here_doc) == -1)
		return (-1);
	if ((here_doc = open(file_name, O_RDONLY)) == -1)
		return (-1);
	unlink(file_name);
	return (here_doc);
}
