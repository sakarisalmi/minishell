/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_unpacker_pipe_and_redir.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:10:18 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/26 13:59:02 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/tokenizer.h"

/*	This function marks pipes and redirections for the later
	tokenizer function.
	Why is this function needed? Because the token unpacker function will
	remove the quotation marks from the read_line_part for the token_string,
	so we cannot check if the pipe or redirection had quotation marks around
	it later. */
void	token_unpacker_pipe_and_redir(t_token *token, char *rl_part)
{
	if (ft_strncmp(rl_part, "|", 2) == 0)
		token->type = T_PIPE;
	if (ft_strncmp(rl_part, ">", 2) == 0 || ft_strncmp(rl_part, "<", 2) == 0
		|| ft_strncmp(rl_part, ">>", 3) == 0
		|| ft_strncmp(rl_part, "<<", 3) == 0)
		token->type = T_REDIR;
}
