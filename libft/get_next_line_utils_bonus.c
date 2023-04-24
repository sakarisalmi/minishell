/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:05:19 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/28 16:21:17 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(const char *s);
char	*gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *static_line, char *buffer);
char	*gnl_get_single_line(char *str);
char	*gnl_trim_static_line(char *old_str);

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char	*gnl_strchr(char *s, int c)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*gnl_strjoin(char *static_line, char *buffer)
{
	unsigned int		len;
	unsigned int		j;
	char				*str;

	len = 0;
	j = 0;
	if (!static_line)
	{
		static_line = (char *)malloc(sizeof(char) * 1);
		static_line[0] = '\0';
	}
	if (!static_line || !buffer)
		return (NULL);
	str = (char *)malloc((gnl_strlen(static_line) + gnl_strlen(buffer)
				+ 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (static_line[j])
		str[len++] = static_line[j++];
	j = 0;
	while (buffer[j])
		str[len++] = buffer[j++];
	str[len] = '\0';
	free(static_line);
	return (str);
}

char	*gnl_get_single_line(char *static_line)
{
	char	*single_line;
	int		len;
	int		i;

	len = 0;
	i = -1;
	if (!static_line)
		return (NULL);
	while (static_line[len] && static_line[len] != '\n')
		len++;
	if (static_line[len] == '\n')
		len++;
	single_line = (char *)malloc(sizeof(char) * (len + 1));
	if (!single_line)
		return (NULL);
	while (++i < len)
		single_line[i] = static_line[i];
	single_line[i] = '\0';
	if (single_line[0] != '\0')
		return (single_line);
	else
	{
		free(single_line);
		return (NULL);
	}
}

char	*gnl_trim_static_line(char *old_str)
{
	unsigned int		i;
	unsigned int		j;
	char				*new_str;

	i = 0;
	while (old_str[i] && old_str[i] != '\n')
		i++;
	if (!old_str[i])
	{
		free(old_str);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (gnl_strlen(old_str) - i + 1));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (old_str[i])
			new_str[j++] = old_str[i++];
	new_str[j] = '\0';
	free(old_str);
	if (new_str[0] != '\0')
		return (new_str);
	free(new_str);
	return (NULL);
}
