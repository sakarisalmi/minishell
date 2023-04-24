/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:05:07 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/28 16:21:07 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd);
char	*gnl_read_next_line(int fd, char *static_line);

char	*get_next_line(int fd)
{
	static char	*static_line[OPEN_MAX];
	char		*single_line;

	if (fd < 0 || fd > OPEN_MAX || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_line[fd] = gnl_read_next_line(fd, static_line[fd]);
	if (!static_line[fd])
		return (NULL);
	single_line = gnl_get_single_line(static_line[fd]);
	static_line[fd] = gnl_trim_static_line(static_line[fd]);
	return (single_line);
}

char	*gnl_read_next_line(int fd, char *static_line)
{
	char	*buffer;
	int		read_bytes;
	int		i;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes != 0 && !gnl_strchr(static_line, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		if (read_bytes != 0)
			static_line = gnl_strjoin(static_line, buffer);
	}
	i = -1;
	while (buffer[++i] != '\0')
		buffer[i] = '\0';
	free(buffer);
	return (static_line);
}
