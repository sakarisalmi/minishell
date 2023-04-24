/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:13:43 by ssalmi            #+#    #+#             */
/*   Updated: 2022/12/23 16:47:49 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_printf(const char *format, ...);
static int	ft_formats(char c, va_list argp);
static int	ft_put_sig_nbr(long long int nbr);
static int	ft_put_unsig_nbr(unsigned long long int nbr, int base, char c);

int	ft_printf(const char *format, ...)
{
	int		length;
	va_list	argp;

	length = 0;
	va_start(argp, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '\0')
		{
			format++;
			length += ft_formats(*format, argp);
		}
		else if (*format == '%')
			length--;
		else
			length += ft_prf_putchar(*format);
		format++;
	}
	va_end(argp);
	return (length);
}

static int	ft_formats(char c, va_list argp)
{
	int	length;

	length = 0;
	if (c == 'c')
		length += ft_prf_putchar(va_arg(argp, int));
	else if (c == 's')
		length += ft_prf_putstr(va_arg(argp, char *));
	else if (c == 'p')
		length += ft_put_unsig_nbr(va_arg(argp, unsigned long), 16, c);
	else if (c == 'd' || c == 'i')
		length += ft_put_sig_nbr(va_arg(argp, int));
	else if (c == 'u')
		length += ft_put_unsig_nbr(va_arg(argp, unsigned int), 10, c);
	else if (c == 'x' || c == 'X')
		length += ft_put_unsig_nbr(va_arg(argp, unsigned int), 16, c);
	else if (c == '%')
		length += ft_prf_putchar('%');
	return (length);
}

static int	ft_put_sig_nbr(long long int nbr)
{
	char	buffer[20];
	char	*result;
	char	*digits;
	int		len;

	result = &buffer[19];
	len = 0;
	*result = '\0';
	digits = "0123456789";
	if (nbr == 0)
		len += ft_prf_putchar('0');
	if (nbr < 0)
	{
		len += ft_prf_putchar('-');
		nbr *= -1;
	}
	while (nbr != 0)
	{
		*--result = digits[nbr % 10];
		nbr = nbr / 10;
	}
	len += ft_prf_putstr(result);
	return (len);
}

static int	ft_put_unsig_nbr(unsigned long long int nbr, int base, char c)
{
	char	buffer[20];
	char	*result;
	char	*digits;
	int		len;

	result = &buffer[19];
	len = 0;
	*result = '\0';
	if (c == 'p')
		len += ft_prf_putstr("0x");
	digits = "0123456789abcdef";
	if (c == 'X')
		digits = "0123456789ABCDEF";
	if (nbr == 0)
		len += ft_prf_putchar('0');
	while (nbr != 0)
	{
		*--result = digits[nbr % base];
		nbr = nbr / base;
	}
	len += ft_prf_putstr(result);
	return (len);
}
