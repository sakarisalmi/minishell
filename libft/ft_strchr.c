/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:38:23 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/25 12:25:26 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	c_char;

	str = (char *)s;
	c_char = (char)c;
	while (*str)
	{
		if (*str == c_char)
			return (str);
		str++;
	}
	if (*str == c_char)
		return (str);
	return (NULL);
}
