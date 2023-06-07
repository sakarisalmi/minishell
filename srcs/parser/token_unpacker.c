/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_unpacker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:37:49 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/07 16:25:01 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

int				token_unpacker(char *rl_part, t_token *token,
					t_token_unpacker *f, t_data *data);
static int		token_unpacker_outside_quotes(char *rl_part, char *token,
					t_token_unpacker *f, t_data *data);
static int		token_unpacker_in_quotes(char *rl_part, char *token,
					t_token_unpacker *f, t_data *data);
static int		token_unpacker_in_s_quotes(char *rl_part, char *token,
					t_token_unpacker *f);
static int		token_unpacker_set_err(t_token_unpacker *f,
					int error_code, int error_idx);

/*----------------------------------------------------------------------------*/

/*	This function handles the "unpacking" of the rl_parts into tokens.
	If we encounter an error in the rl_part (for example, an "unpaired quote"
	or forbidden symbol) we set the error code, print error
	and end the function.
	first malloc token size to be the same as the rl_part size.*/
int	token_unpacker(char *rl_part, t_token *token,
	t_token_unpacker *f, t_data *data)
{
	token->rl_part_string = ft_strdup(rl_part);
	while (rl_part[f->i])
	{
		if (rl_part[f->i] == '\"')
		{
			if (token_unpacker_in_quotes(rl_part, token->string,
					f, data) != 0)
				return (tunp_error_msg(f->error_code,
						rl_part[f->error_idx]));
		}				
		else if (rl_part[f->i] == '\'')
		{
			if (token_unpacker_in_s_quotes(rl_part, token->string, f) != 0)
				return (tunp_error_msg(f->error_code, rl_part[f->error_idx]));
		}
		else
		{
			if (token_unpacker_outside_quotes(rl_part, token->string,
					f, data) != 0)
				return (tunp_error_msg(f->error_code,
						rl_part[f->error_idx]));
		}
	}
	token_unpacker_end(token, rl_part);
	return (0);
}

static int	token_unpacker_outside_quotes(char *rl_part, char *token,
	t_token_unpacker *f, t_data *data)
{
	while (rl_part[f->i])
	{
		if (rl_part[f->i] == '$')
		{
			token = token_unpacker_hit_var(rl_part, token, f, data);
			token_lst_last(data->parser.token_lst)->string = token;
			continue ;
		}
		if (rl_part[f->i] == '\'' || rl_part[f->i] == '"')
			return (0);
		ft_strncat(token, rl_part + f->i, 1);
		f->i++;
	}
	return (0);
}

static int	token_unpacker_in_quotes(char *rl_part, char *token,
	t_token_unpacker *f, t_data *data)
{
	f->in_quotes = 1;
	f->k = f->i;
	f->i++;
	while (rl_part[f->i])
	{
		if (rl_part[f->i] == '$')
		{
			token = token_unpacker_hit_var(rl_part, token, f, data);
			token_lst_last(data->parser.token_lst)->string = token;
			continue ;
		}
		if (rl_part[f->i] == '"')
		{
			f->i++;
			f->in_quotes = 0;
			return (0);
		}
		ft_strncat(token, &rl_part[f->i], 1);
		f->i++;
	}
	if (f->in_quotes)
		return (token_unpacker_set_err(f, T_UNPAIRED_QUOTE, f->k));
	return (0);
}

static int	token_unpacker_in_s_quotes(char *rl_part, char *token,
	t_token_unpacker *f)
{
	f->in_single_quotes = 1;
	f->k = f->i;
	f->i++;
	while (rl_part[f->i])
	{
		if (rl_part[f->i] == '\'')
		{
			f->i++;
			f->in_single_quotes = 0;
			return (0);
		}
		ft_strncat(token, &rl_part[f->i], 1);
		f->i++;
	}
	if (f->in_single_quotes)
		return (token_unpacker_set_err(f, T_UNPAIRED_S_QUOTE, f->k));
	return (0);
}

static int	token_unpacker_set_err(t_token_unpacker *f,
	int error_code, int error_idx)
{
	f->error_code = error_code;
	f->error_idx = error_idx;
	return (1);
}
