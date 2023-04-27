/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_error_msg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:01:05 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/25 15:27:24 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"

int	tok_error_msg(char c)
{
	// print in stderror
	if (c == '\0')
		printf("MINISHELL: syntax error near unexpected token `newline\'\n");
	else
		printf("MINISHELL: syntax error near unexpected token `%c\'\n", c);
	return (258);
}
