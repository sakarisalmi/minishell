/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:09:13 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/08 12:54:31 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1temp;
	unsigned char	*s2temp;
	size_t			index;
	int				result;

	s1temp = (unsigned char *)s1;
	s2temp = (unsigned char *)s2;
	index = 0;
	if (n == 0)
		return (0);
	while (s1temp[index] == s2temp[index] && index < n - 1)
	{
		index++;
	}
	result = (s1temp[index]) - (s2temp[index]);
	return (result);
}
