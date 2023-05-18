/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_unpacker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:37:49 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/18 15:49:16 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

#define FORBIDDEN_SYMBOLS "\\;&"

int				token_unpacker(char *rl_part, t_token *token,
					t_token_unpacker *tunp, t_data *data);
static int		token_unpacker_outside_quotes(char *rl_part, char *token,
					t_token_unpacker *tunp, t_data *data);
static int		token_unpacker_in_quotes(char *rl_part, char *token,
					t_token_unpacker *tunp, t_data *data);
static int		token_unpacker_in_s_quotes(char *rl_part, char *token,
					t_token_unpacker *tunp);
static int		token_unpacker_set_err(t_token_unpacker *tunp,
					int error_code, int error_idx);

/*----------------------------------------------------------------------------*/

/*	This function handles the "unpacking" of the rl_parts into tokens.
	If we encounter an error in the rl_part (for example, an "unpaired quote"
	or forbidden symbol) we set the error code, print error
	and end the function.
	first malloc token size to be the same as the rl_part size.*/
int	token_unpacker(char *rl_part, t_token *token,
	t_token_unpacker *tunp, t_data *data)
{
	while (rl_part[tunp->i])
	{
		if (rl_part[tunp->i] == '\"')
		{
			if (token_unpacker_in_quotes(rl_part, token->string,
					tunp, data) != 0)
				return (tunp_error_msg(tunp->error_code,
						rl_part[tunp->error_idx]));
		}				
		else if (rl_part[tunp->i] == '\'')
		{
			if (token_unpacker_in_s_quotes(rl_part, token->string, tunp) != 0)
				return (tunp_error_msg(tunp->error_code,
						rl_part[tunp->error_idx]));
		}
		else
		{
			if (token_unpacker_outside_quotes(rl_part, token->string,
					tunp, data) != 0)
				return (tunp_error_msg(tunp->error_code,
						rl_part[tunp->error_idx]));
		}
	}
	token_unpacker_pipe_and_redir(token, rl_part);
	return (0);
}

static int	token_unpacker_outside_quotes(char *rl_part, char *token,
	t_token_unpacker *tunp, t_data *data)
{
	while (rl_part[tunp->i])
	{
		if (ft_strchr(FORBIDDEN_SYMBOLS, rl_part[tunp->i]))
		{
			tunp->error_code = T_FORBIDDEN_SYMBOL;
			tunp->error_idx = tunp->i;
			return (2);
		}
		if (rl_part[tunp->i] == '$')
		{
			token = token_unpacker_hit_var(rl_part, token, tunp, data);
			token_lst_last(data->parser.token_lst)->string = token;
			continue ;
		}
		if (rl_part[tunp->i] == '\'' || rl_part[tunp->i] == '"')
			return (0);
		ft_strncat(token, rl_part + tunp->i, 1);
		tunp->i++;
	}
	return (0);
}

static int	token_unpacker_in_quotes(char *rl_part, char *token,
	t_token_unpacker *tunp, t_data *data)
{
	tunp->in_quotes = 1;
	tunp->k = tunp->i;
	tunp->i++;
	while (rl_part[tunp->i])
	{
		if (rl_part[tunp->i] == '$')
		{
			token = token_unpacker_hit_var(rl_part, token, tunp, data);
			token_lst_last(data->parser.token_lst)->string = token;
			continue ;
		}
		if (rl_part[tunp->i] == '"')
		{
			tunp->i++;
			tunp->in_quotes = 0;
			return (0);
		}
		ft_strncat(token, &rl_part[tunp->i], 1);
		tunp->i++;
	}
	if (tunp->in_quotes)
		return (token_unpacker_set_err(tunp, T_UNPAIRED_QUOTE, tunp->k));
	return (0);
}

static int	token_unpacker_in_s_quotes(char *rl_part, char *token,
	t_token_unpacker *tunp)
{
	tunp->in_single_quotes = 1;
	tunp->k = tunp->i;
	tunp->i++;
	while (rl_part[tunp->i])
	{
		if (rl_part[tunp->i] == '\'')
		{
			tunp->i++;
			tunp->in_single_quotes = 0;
			return (0);
		}
		ft_strncat(token, &rl_part[tunp->i], 1);
		tunp->i++;
	}
	if (tunp->in_single_quotes)
		return (token_unpacker_set_err(tunp, T_UNPAIRED_S_QUOTE, tunp->k));
	return (0);
}

static int	token_unpacker_set_err(t_token_unpacker *tunp,
	int error_code, int error_idx)
{
	tunp->error_code = error_code;
	tunp->error_idx = error_idx;
	return (1);
}
