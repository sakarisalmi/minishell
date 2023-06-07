/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_set_token_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:44:44 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/07 16:33:04 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"

void			tok_set_token_args(t_token *token, t_data *data);
static t_token	*tok_skip_redir_and_ingore(t_token *token);

/*----------------------------------------------------------------------------*/

/*	This function set the args for a token. It also sets the token's argument
	tokens' types as T_ARG.

	If the token_type is T_REDIR, we set only the next token as argument.
	If the token_type is T_COMMAND, we set as many tokens as
	arguments as possible.

	if the token is T_REDIR, we create an array of strings that has only one
	string in it.
	If the token is T_COMMAND, we set the arguments' strings in an array of
	strings that ends in a NULL pointer. */
void	tok_set_token_args(t_token *token, t_data *data)
{
	t_token	*tmp_token;

	if (token->type == T_REDIR)
	{
		token->next->type = T_ARG;
		token->args = ms_calloc(1, sizeof(char *), data);
		token->args[0] = token->next->string;
	}
	else if (token->type == T_COMMAND)
	{
		token->args = ms_calloc(1, sizeof(char *), data);
		token->args = str_array_add_str(token->args, token->string);
		tmp_token = token->next;
		while (tmp_token && tmp_token->type != T_PIPE)
		{
			if (tmp_token->type == T_REDIR || tmp_token->type == T_IGNORE)
				tmp_token = tok_skip_redir_and_ingore(tmp_token);
			else
			{
				tmp_token->type = T_ARG;
				token->args = str_array_add_str(token->args, tmp_token->string);
				tmp_token = tmp_token->next;
			}
		}
	}
}

static t_token	*tok_skip_redir_and_ingore(t_token *token)
{
	t_token	*tmp;

	if (token->type == T_IGNORE)
		return (token->next);
	tmp = token->next;
	if (!tmp)
		return (tmp);
	else
		return (tmp->next);
}
