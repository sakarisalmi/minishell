/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:11:37 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/08 16:04:04 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_needle(const char *haystack, const char *needle, size_t len);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		result;

	i = 0;
	while (needle[i])
		i++;
	if (i == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	result = find_needle(haystack, needle, len);
	if (result == -1)
		return (NULL);
	else
		return ((char *)haystack + (result));
}

static int	find_needle(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (len < 0)
		len = ft_strlen(haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		if (needle[j] == haystack[i])
		{
			k = i;
			while (needle[j] == haystack[k] && needle[j] != '\0' && k < len)
			{
				j++;
				k++;
			}
			if (needle[j] == '\0')
				return (k - j);
		}
		i++;
	}
	return (-1);
}
