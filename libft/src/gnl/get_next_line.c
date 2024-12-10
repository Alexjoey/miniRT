/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 00:57:57 by amylle            #+#    #+#             */
/*   Updated: 2024/03/11 17:15:26 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
/*
char	*getskipline(char **buffer)
{
	char	*ret;
	char	*nxtline;
	char	*temp;

	nxtline = ft_strchr(*buffer, '\n');
	if (!nxtline)
	{
		temp = *buffer;
		free (*buffer);
		*buffer = NULL;
		return (temp);
	}
	ret = ft_substr(*buffer, 0, nxtline - *buffer + 1);
	temp = ft_substr(*buffer, nxtline - *buffer + 1, \
			*buffer + ft_strlen(*buffer) - nxtline);
	free (*buffer);
	*buffer = temp;
	return (ret);
}
*/

static char	*ft_getline(char *buffer)
{
	char	*nextline;
	char	*line;

	if (!buffer[0])
		return (NULL);
	nextline = ft_strchr(buffer, '\n');
	if (nextline)
		line = ft_substr(buffer, 0, nextline - buffer + 1);
	else
		line = ft_substr(buffer, 0, ft_strlen(buffer) + 1);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_getbuffer(char *buffer)
{
	char	*nextline;
	char	*temp;

	temp = NULL;
	nextline = ft_strchr(buffer, '\n');
	if (nextline && *(nextline + 1) != 0)
		temp = ft_substr(nextline + 1, 0, ft_strlen(nextline + 1));
	free (buffer);
	if (!nextline || !temp)
		return (NULL);
	return (temp);
}

static char	*read_file(int fd, char *str)
{
	char	*buffer;
	int		readret;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	readret = 1;
	while (!ft_strchr(str, '\n') && readret > 0)
	{
		readret = read(fd, buffer, BUFFER_SIZE);
		if (readret == -1)
		{
			free (buffer);
			free (str);
			return (NULL);
		}
		buffer[readret] = 0;
		str = ft_strjoinfree(str, buffer);
	}
	free (buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_getline(buffer[fd]);
	buffer[fd] = ft_getbuffer(buffer[fd]);
	return (line);
}

char	*gnl_nobuffer(int fd)
{
	char	*line;
	char	*pointer;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_file(fd, line);
	if (!line)
		return (NULL);
	pointer = ft_strchr(line, '\n');
	if (pointer)
		pointer[1] = 0;
	return (line);
}
