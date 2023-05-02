/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_unpacker_error_msg.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:18:13 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/02 14:48:06 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

/*	make it so that the error message prints in the stderror!	*/
int	tunp_error_msg(int error_code, char error_char)
{
	if (error_code == T_UNPAIRED_QUOTE)
		ft_putendl_fd("MINISHELL: parse error; unpaired quote `\"\'", 2);
	else if (error_code == T_UNPAIRED_S_QUOTE)
		ft_putendl_fd("MINISHELL: parse error; unpaired quote `\'\'", 2);
	else if (error_code == T_FORBIDDEN_SYMBOL)
	{
		ft_putstr_fd("MINISHELL: parse error; forbidden symbol `", 2);
		ft_putchar_fd(error_char, 2);
		ft_putendl_fd("\'", 2);
	}
	else
		ft_putendl_fd("MINISHELL: parse error; unidentified error!", 2);
	return (258);
}
