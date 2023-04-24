/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:40:54 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/24 14:50:30 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenize.h"

static void	init_rl_split_struct(t_rl_split *t);
void		read_line_split(char *line, t_list **rl_parts_ls,
				int *token_amount);

/*----------------------------------------------------------------------------*/

static void	init_rl_split_struct(t_rl_split *t)
{
	t->i = 0;
	t->j = 0;
	t->in_quotes = 0;
	t->in_single_quotes = 0;
	t->in_token = 0;
}

void	read_line_split(char *line, t_list **rl_parts_ls, int *token_amount)
{
	t_rl_split	t;

	init_rl_split_struct(&t);
	while (line[t.i] != '\0')
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
}

// static void	init_rl_split_struct(t_rl_split *t)
// {
// 	t->i = 0;
// 	t->j = 0;
// 	t->in_quotes = 0;
// 	t->in_single_quotes = 0;
// 	t->in_token = 0;
// }

// void	read_line_split(char *line, char *rl_parts[], int *token_amount)
// {
// 	t_rl_split	t;

// 	init_rl_split_struct(&t);
// 	while (line[t.i] != '\0')
// 	{
// 		if (line[t.i] == '"' && !t.in_single_quotes)
// 			rl_s_handle_quotes(line, rl_parts, &t);
// 		else if (line[t.i] == '\'' && !t.in_quotes)
// 			rl_s_handle_s_quotes(line, rl_parts, &t);
// 		else if ((line[t.i] == '>' || line[t.i] == '<' || line[t.i] == '|')
// 			&& !t.in_quotes && !t.in_single_quotes)
// 			rl_s_handle_redir_pipe(line, rl_parts, &t);
// 		else
// 			rl_s_handle_whitespace(line, rl_parts, &t);
// 		t.i++;
// 	}
// 	if (t.in_token)
// 		t.j++;
// 	*token_amount = t.j;
// }
