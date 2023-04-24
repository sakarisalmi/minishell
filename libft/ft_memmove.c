/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:23:21 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/01 14:54:20 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*srctemp;
	unsigned char		*dsttemp;
	size_t				i;

	if (!src && !dst)
		return (NULL);
	srctemp = (unsigned char *)src;
	dsttemp = (unsigned char *)dst;
	i = 0;
	if (src <= dst)
	{
		while (len--)
			dsttemp[len] = srctemp[len];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
