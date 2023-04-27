/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:43:40 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/27 15:08:02 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

int			tokens_creator(t_parser *parser, t_data *data);
static void	set_token_unpacker_values(t_token_unpacker *tunp);

/*----------------------------------------------------------------------------*/

/*	This function creates tokens from the rl_parts. This happens with the help
	of the token_unpacker function.
	Also the double quotes and single quotes stuff */
int	tokens_creator(t_parser *parser, t_data *data)
{
	t_token_unpacker	tunp;
	t_list				*rl_parts_lst_tmp;
	int					i;

	i = -1;
	rl_parts_lst_tmp = parser->rl_parts_lst;
	while (++i < parser->token_amount)
	{
		token_lst_addback(&parser->token_lst, token_lst_init_new_node(ft_calloc
				(ft_strlen(rl_parts_lst_tmp->content) + 1, sizeof(char))));
		set_token_unpacker_values(&tunp);
		token_unpacker((char *)rl_parts_lst_tmp->content,
			token_lst_last(parser->token_lst),
			&tunp, data);
		rl_parts_lst_tmp = rl_parts_lst_tmp->next;
		if (tunp.error_code != 0)
		{
			printf("TUNP ERROR, freeing shit (tunp.error_code: %d)\n", tunp.error_code);
			ft_lstclear(&data->parser.rl_parts_lst, free);
			token_lst_clear_ls(&data->parser.token_lst);
			return (1);
		}
	}
	return (0);
}

static void	set_token_unpacker_values(t_token_unpacker *tunp)
{
	tunp->i = 0;
	tunp->j = 0;
	tunp->k = 0;
	tunp->in_quotes = 0;
	tunp->in_single_quotes = 0;
	tunp->error_code = T_NO_ERROR;
	tunp->error_idx = 0;
}
