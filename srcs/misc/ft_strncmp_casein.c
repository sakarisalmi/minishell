/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_casein.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:44:24 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/09 14:05:35 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strncmp_casein(const char *s1, const char *s2, size_t n)
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
	while (ft_tolower(*uns1) == ft_tolower(*uns2) && *uns1 != '\0'
		&& *uns2 != '\0' && index < n - 1)
	{
		uns1++;
		uns2++;
		index++;
	}
	result = ft_tolower(*uns1) - ft_tolower(*uns2);
	if (result > 0)
		result = 1;
	else if (result < 0)
		result = -1;
	return (result);
}
