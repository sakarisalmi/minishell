/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_error_msg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:01:05 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/02 15:20:29 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"

int	tok_error_msg(char c)
{
	if (c == '\0')
	{
		ft_putstr_fd("MINISHELL: syntax error near unexpected ", 2);
		ft_putendl_fd("token `newline\'", 2);
	}
	else
	{
		ft_putstr_fd("MINISHELL: syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putendl_fd("\'", 2);
	}
	return (258);
}
