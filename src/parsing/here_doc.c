/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:46:47 by jpiquet           #+#    #+#             */
/*   Updated: 2025/09/11 11:11:51 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <fcntl.h>

int	sig_int_received(t_mini *mini, int here_doc, int here_doc_copy)
{
	close(here_doc);
	close(here_doc_copy);
	mini->exit_status = 130;
	return (-2);
}

int	open_here_doc(int *here_doc, int *here_doc_copy, char *file_name)
{
	*here_doc = open(file_name, O_WRONLY | O_CREAT, 0664);
	if (*here_doc == -1)
		return (-1);
	*here_doc_copy = open(file_name, O_RDONLY);
	if (*here_doc_copy == -1)
		return (-1);
	if (unlink(file_name))
		return (-1);
	return (0);
}

int	read_here_doc(t_heredoc *hd, char *eof, t_mini *mini)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (g_sig_flag == 1)
			return (sig_int_received(mini, hd->here_doc, hd->here_doc_copy));
		if (!line)
		{
			print_error_here_doc(eof);
			break ;
		}
		if (ft_strcmp(line, eof))
		{
			free(line);
			break ;
		}
		if (ft_strchr(line, '$') && hd->had_quote == false)
			line = handle_env_var_for_here_doc(line, mini);
		ft_putstr_fd(line, hd->here_doc);
		ft_putchar_fd('\n', hd->here_doc);
		free(line);
	}
	return (0);
}

int	create_here_doc(t_mini *mini, char *eof, t_gmalloc **head)
{
	char		*file_name;
	int			check_read;
	t_heredoc	hd;

	hd.had_quote = false;
	file_name = generate_rand_name_file(head);
	if (!file_name)
		return (-1);
	if (ft_strchr(eof, DQ) || ft_strchr(eof, SQ))
	{
		hd.had_quote = true;
		eof = delete_quote(eof);
	}
	if (open_here_doc(&hd.here_doc, &hd.here_doc_copy, file_name) == -1)
		return (-1);
	check_read = read_here_doc(&hd, eof, mini);
	if (check_read == -2)
		return (-2);
	close(hd.here_doc);
	return (hd.here_doc_copy);
}
