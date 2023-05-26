/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:40:54 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/26 11:43:51 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

int			read_line_split(char *line, t_list **rl_parts_ls,
				int *token_amount);
static void	init_rl_split_struct(t_rl_split *t);

/*----------------------------------------------------------------------------*/

int	read_line_split(char *line, t_list **rl_parts_ls, int *token_amount)
{
	t_rl_split	t;

	init_rl_split_struct(&t);
	while (line[t.i] != '\0' && !t.failure)
	{
		if (line[t.i] == '"' && !t.in_single_quotes)
			rl_s_handle_quotes(line, rl_parts_ls, &t);
		else if (line[t.i] == '\'' && !t.in_quotes)
			rl_s_handle_s_quotes(line, rl_parts_ls, &t);
		else if ((line[t.i] == '>' || line[t.i] == '<' || line[t.i] == '|')
			&& !t.in_quotes && !t.in_single_quotes)
			rl_s_handle_redir_pipe(line, rl_parts_ls, &t);
		else
			rl_s_handle_whitespace(line, rl_parts_ls, &t);
		t.i++;
	}
	if (t.in_token)
		t.j++;
	*token_amount = t.j;
	if (t.failure)
		return (1);
	return (0);
}

static void	init_rl_split_struct(t_rl_split *t)
{
	t->i = 0;
	t->j = 0;
	t->in_quotes = 0;
	t->in_single_quotes = 0;
	t->in_token = 0;
	t->failure = 0;
}
