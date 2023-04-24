/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:51:42 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/08 13:50:25 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	int				result;
	unsigned char	*uns1;
	unsigned char	*uns2;

	uns1 = (unsigned char *)s1;
	uns2 = (unsigned char *)s2;
	index = 0;
	if (n == 0)
		return (0);
	while (*uns1 == *uns2 && *uns1 != '\0'
		&& *uns2 != '\0' && index < n - 1)
	{
		uns1++;
		uns2++;
		index++;
	}
	result = *uns1 - *uns2;
	if (result > 0)
		result = 1;
	else if (result < 0)
		result = -1;
	return (result);
}
