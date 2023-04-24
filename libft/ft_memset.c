/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:27:53 by ssalmi            #+#    #+#             */
/*   Updated: 2022/10/29 12:41:17 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char		*str;
	size_t				idx;

	idx = 0;
	str = (unsigned char *)b;
	while (idx < len)
	{
		str[idx] = (char)c;
		idx++;
	}
	return (b);
}
