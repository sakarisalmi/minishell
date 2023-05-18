/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:40:57 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/17 16:33:04 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_isspace(char c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strncat(char *dest, const char *src, size_t n);
void	*ft_realloc(void *ptr, size_t size);

/*----------------------------------------------------------------------------*/

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\f' || c == '\v');
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*temp;

	temp = dest;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = '\0';
	return (temp);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	unsigned int	len1;
	unsigned int	len2;

	len1 = ft_strlen(dest);
	len2 = ft_strlen(src);
	if (len2 < n)
		ft_strcpy(&dest[len1], src);
	else
	{
		ft_strncpy(&dest[len1], src, n);
		dest[len1 + n] = '\0';
	}
	return (dest);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (size)
	{
		if (!ptr)
			return (malloc(size));
		new_ptr = malloc(size);
		if (new_ptr)
		{
			ft_memcpy(new_ptr, ptr, size);
			free(ptr);
		}
	}
	return (new_ptr);
}
