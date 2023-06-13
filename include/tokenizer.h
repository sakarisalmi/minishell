/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:25:32 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/07 14:51:06 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

enum e_token_type
{
	T_UNIDENTIFIED,
	T_COMMAND,
	T_ARG,
	T_PIPE,
	T_REDIR,
	T_IGNORE
};

/*----------------------------------------------------------------------------*/

// tokenizer.c
int		tokenizer(t_token *token_lst, t_data *data);

// tokenizer_error_msg.c
int		tok_error_msg(char c);

// tokenizer_set_token_args.c
void	tok_set_token_args(t_token *token, t_data *data);

#endif