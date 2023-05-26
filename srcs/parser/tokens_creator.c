/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:43:40 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/26 16:24:41 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

int			tokens_creator(t_parser *parser, t_data *data);
static void	set_token_unpacker_values(t_token_unpacker *tunp,
				int rl_part_length);

/*----------------------------------------------------------------------------*/

/*	This function creates tokens from the rl_parts. This happens with the help
	of the token_unpacker function.
	Also the double quotes and single quotes stuff */
int	tokens_creator(t_parser *parser, t_data *data)
{
	t_token_unpacker	tunp;
	t_list				*rl_parts_lst_tmp;
	int					result;
	int					i;

	i = -1;
	rl_parts_lst_tmp = parser->rl_parts_lst;
	while (++i < parser->token_amount)
	{
		token_lst_addback(&parser->token_lst, token_lst_init_new_node(ft_calloc(\
		ft_strlen(rl_parts_lst_tmp->content) + 1, sizeof(char)), data));
		set_token_unpacker_values(&tunp,
			ft_strlen(rl_parts_lst_tmp->content) + 1);
		result = token_unpacker(rl_parts_lst_tmp->content,
				token_lst_last(parser->token_lst), &tunp, data);
		if (result != 0)
		{
			data->latest_exit_status = result;
			return (result);
		}
		rl_parts_lst_tmp = rl_parts_lst_tmp->next;
	}
	return (0);
}

static void	set_token_unpacker_values(t_token_unpacker *tunp,
	int rl_part_length)
{
	tunp->i = 0;
	tunp->j = 0;
	tunp->k = 0;
	tunp->token_length = rl_part_length;
	tunp->in_quotes = 0;
	tunp->in_single_quotes = 0;
	tunp->error_code = T_NO_ERROR;
	tunp->error_idx = 0;
}
