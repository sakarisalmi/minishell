/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:15:43 by ssalmi            #+#    #+#             */
/*   Updated: 2022/11/07 12:40:34 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_str_size(int nbr);
static void		min_int(char *s, int n, int i);

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (get_str_size(n) + 1));
	if (!str)
		return (NULL);
	str[get_str_size(n)] = '\0';
	i = get_str_size(n) - 1;
	if (n == 0)
		(str[0] = '0');
	if (n == -2147483647 - 1)
		min_int(str, n, i);
	else if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[i--] = (n % 10) + 48;
		n = n / 10;
	}
	return (str);
}

static int	get_str_size(int nbr)
{
	int	nbr_copy;
	int	digit_amount;

	nbr_copy = nbr;
	digit_amount = 0;
	if (nbr_copy < 0)
	{
		if (nbr_copy == -2147483648)
			return (11);
		nbr_copy *= -1;
		digit_amount++;
	}
	while (nbr_copy >= 10)
	{
		nbr_copy = nbr_copy / 10;
		digit_amount++;
	}
	digit_amount++;
	return (digit_amount);
}

static void	min_int(char *s, int n, int i)
{
	s[0] = '-';
	s[i--] = '8';
	n = 214748364;
	while (n > 0)
	{
		s[i--] = (n % 10) + 48;
		n = n / 10;
	}
}
