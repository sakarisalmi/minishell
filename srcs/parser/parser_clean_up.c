/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_up.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:18:41 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/22 17:24:18 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/tokenizer.h"

void	tokens_clean_up(t_data *data);
void	read_line_clean_up(t_data *data, char *read_line);

/*----------------------------------------------------------------------------*/

/*	This function handles the freeing of everything allocated for the tokens
	ands sets it so that there is a "clean" slate for the next time the
	user is writing their commands. */
void	tokens_clean_up(t_data *data)
{
	t_token	*tmp1;
	t_token	*tmp2;

	tmp1 = data->parser.token_lst;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		if (tmp1->string)
			free(tmp1->string);
		if (tmp1->args)
			free(tmp1->args);
		tmp1->type = T_UNIDENTIFIED;
		free(tmp1);
		tmp1 = tmp2;
	}
	data->parser.token_amount = 0;
	data->parser.token_lst = NULL;
}

/*	This function handle the freeing of everything allocated for the
	read_line and the rl_parts.*/
void	read_line_clean_up(t_data *data, char *read_line)
{
	if (read_line)
		free(read_line);
	read_line = NULL;
	ft_lstclear(&data->parser.rl_parts_lst, free);
	data->parser.rl_parts_lst = NULL;
}
