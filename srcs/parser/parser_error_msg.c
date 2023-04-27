/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:18:13 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/25 14:22:37 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

/*	make it so that the error message prints in the stderror!	*/
int	parser_error_msg(int error_code, char error_char)
{
	if (error_code == T_UNPAIRED_QUOTE)
		printf("Minishell: parse error; unpaired `\"\'\n");
	if (error_code == T_UNPAIRED_S_QUOTE)
		printf("Minishell: parse error; unpaired `\'\'\n");
	if (error_code == T_FORBIDDEN_SYMBOL)
		printf("Minishell: parse error; forbidden symbol `%c\'\n",
			error_char);
	if (error_code == T_PARSE_ERROR && error_char == '\n')
		printf("Minishell: parse error near `\\n\'\n");
	else if (error_code == T_PARSE_ERROR)
		printf("Minishell: parse error near `%c\'", error_char);
	return (error_code);
}
