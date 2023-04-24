/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:39:48 by ssalmi            #+#    #+#             */
/*   Updated: 2023/01/04 12:52:07 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_prf_putchar(int c);
int	ft_prf_putstr(char *s);

int	ft_prf_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_prf_putstr(char	*s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		ft_prf_putchar(s[i]);
		i++;
	}
	return (i);
}
