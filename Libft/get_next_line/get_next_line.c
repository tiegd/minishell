/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:21:03 by jpiquet           #+#    #+#             */
/*   Updated: 2024/12/05 18:21:03 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	rest_of_store(char *buf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!buf)
		return ;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	while (buf[i])
		buf[j++] = buf[i++];
	buf[j] = '\0';
}

static char	*store_new_line(char *store)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!store)
		return (NULL);
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	new_line = malloc(sizeof(char) * (i + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (store[i] && store[i] != '\n')
	{
		new_line[i] = store[i];
		i++;
	}
	if (store[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

static char	*read_the_file(int fd, char *store, char *buf)
{
	int		byte_read;

	byte_read = 1;
	while (!ft_strchr(store, '\n') && byte_read > 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1 || !buf[0])
		{
			buf[0] = '\0';
			free(store);
			return (NULL);
		}
		buf[byte_read] = '\0';
		store = ft_strjoin_custom(store, buf);
		if (!store)
			return (NULL);
	}
	if (byte_read == 0 && (!store || store[0] == '\0'))
	{
		free(store);
		return (NULL);
	}
	return (store);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*store;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		buf[0] = '\0';
		return (NULL);
	}
	store = ft_strdup(buf);
	if (!store)
		return (NULL);
	store = read_the_file(fd, store, buf);
	if (!store)
		return (NULL);
	line = store_new_line(store);
	free(store);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	rest_of_store(buf);
	return (line);
}
