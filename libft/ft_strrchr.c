/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:56:04 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/08 15:42:09 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	c_char;
	char	*str;

	str = (char *)s;
	i = ft_strlen(str);
	c_char = (char) c;
	while (i >= 0)
	{
		if (str[i] == c_char)
			return (&str[i]);
		i--;
	}
	return (0);
}
