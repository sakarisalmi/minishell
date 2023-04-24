/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:47 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/01 14:48:35 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dsttemp;
	unsigned char		*srctemp;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	dsttemp = (unsigned char *)dst;
	srctemp = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dsttemp[i] = srctemp[i];
		i++;
	}
	return (dst);
}
