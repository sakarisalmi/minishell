/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:06:42 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/08 13:02:56 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	dstlength;
	size_t	i;
	size_t	j;

	if (!dst)
		dstlength = 0;
	else
		dstlength = ft_strlen(dst);
	srcsize = ft_strlen(src);
	i = dstlength;
	j = 0;
	if (dstsize < i + 1)
		return (srcsize + dstsize);
	while (i + 1 < dstsize && src[j] != '\0')
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (srcsize + dstlength);
}
