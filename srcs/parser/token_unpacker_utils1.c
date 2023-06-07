/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_unpacker_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:18:13 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/07 16:39:17 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/tokenizer.h"

int			tunp_error_msg(int error_code, char error_char);
void		token_unpacker_end(t_token *token, char *rl_part);
static void	token_unpacker_check_if_to_ignore_token(t_token *token,
				char *rl_part);
static void	token_unpacker_pipe_and_redir(t_token *token, char *rl_part);

/*----------------------------------------------------------------------------*/

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

void	token_unpacker_end(t_token *token, char *rl_part)
{
	token_unpacker_pipe_and_redir(token, rl_part);
	token_unpacker_check_if_to_ignore_token(token, rl_part);
}

/*	This function will check if an empty token should be ignored. This will
	happen if the given variable doesn't exist and it isn't
	surrounded by quotes. */
static void	token_unpacker_check_if_to_ignore_token(t_token *token,
	char *rl_part)
{
	if (token->string[0] == '\0')
	{
		if (!ft_strchr(rl_part, '\'') && !ft_strchr(rl_part, '"'))
		{
			token->type = T_IGNORE;
		}
	}
}

/*	This function marks pipes and redirections for the later
	tokenizer function.
	Why is this function needed? Because the token unpacker function will
	remove the quotation marks from the read_line_part for the token_string,
	so we cannot check if the pipe or redirection had quotation marks around
	it later. */
static void	token_unpacker_pipe_and_redir(t_token *token, char *rl_part)
{
	if (ft_strncmp(rl_part, "|", 2) == 0)
		token->type = T_PIPE;
	if (ft_strncmp(rl_part, ">", 2) == 0
		|| ft_strncmp(rl_part, "<", 2) == 0
		|| ft_strncmp(rl_part, ">>", 3) == 0
		|| ft_strncmp(rl_part, "<<", 3) == 0)
		token->type = T_REDIR;
}
