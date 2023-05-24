/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:28:06 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/24 14:16:52 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"

int			tokenizer(t_token *token_lst);
static int	tok_handle_cmd(t_token *token_lst);
static int	tok_pipe(t_token *token);
static int	tok_redir(t_token *token);
static int	tok_handle_pipes_and_redirs(t_token *token_lst);

/*----------------------------------------------------------------------------*/

/*	This is the main tokenizer function.
	
	First we go through every token and check for pipes and redirections;
	we check for any possible errors and return a non-zero value if so.
	If we find redirections we set the args for them.
	
	After going through all of the tokens and doing pipes and redirections
	with their arguments, we go through the tokens again and set the first
	unidentified tokens as commands, and the following unidentified tokens
	as the commands arguments. If we hit a pipe we know that the command has
	no other arguments*/
int	tokenizer(t_token *token_lst)
{
	int	result;

	result = tok_handle_pipes_and_redirs(token_lst);
	if (result != 0)
		return (result);
	tok_handle_cmd(token_lst);
	return (0);
}

static int	tok_handle_cmd(t_token *token_lst)
{
	t_token	*tmp_token;

	tmp_token = token_lst;
	while (tmp_token)
	{
		if (tmp_token->type == T_UNIDENTIFIED)
		{
			tmp_token->type = T_COMMAND;
			tok_set_token_args(tmp_token);
		}
		tmp_token = tmp_token->next;
	}
	return (0);
}

/*	this function checks that the pipe token is legal (ie. no token errors) */
static int	tok_pipe(t_token *token)
{
	if (token->prev == NULL)
		return (tok_error_msg('|'));
	if (token->next == NULL)
		return (tok_error_msg('\0'));
	if (token->next->type == T_PIPE)
		return (tok_error_msg('|'));
	return (0);
}

static int	tok_redir(t_token *token)
{
	if (token->next == NULL)
		return (tok_error_msg('\0'));
	if (token->next->type == T_PIPE)
		return (tok_error_msg('|'));
	if (token->next->type == T_REDIR)
		return (tok_error_msg(token->next->string[0]));
	tok_set_token_args(token);
	return (0);
}

static int	tok_handle_pipes_and_redirs(t_token *token_lst)
{
	t_token	*tmp_token;
	int		result;

	tmp_token = token_lst;
	while (tmp_token)
	{
		if (tmp_token->type == T_PIPE)
		{
			result = tok_pipe(tmp_token);
			if (result != 0)
				return (result);
		}
		if (tmp_token->type == T_REDIR)
		{
			result = tok_redir(tmp_token);
			if (result != 0)
				return (result);
		}
		tmp_token = tmp_token->next;
	}
	return (0);
}
