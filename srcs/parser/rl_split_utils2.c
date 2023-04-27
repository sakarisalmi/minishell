/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_split_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:34:15 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/27 14:38:31 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

void	rl_s_handle_whitespace(char *line, t_list **rl_parts_ls, t_rl_split *t)
{
	if (ft_isspace(line[t->i]) && !t->in_quotes && !t->in_single_quotes)
	{
		if (t->in_token)
		{
			t->in_token = 0;
			t->j++;
		}
	}
	else
	{
		if (!t->in_token)
		{
			ft_lstadd_back(rl_parts_ls,
				ft_lstnew(malloc((ft_strlen(&line[t->i]) + 1) * sizeof(char))));
			t->in_token = 1;
		}
		ft_strncat(ft_lstlast(*rl_parts_ls)->content, &line[t->i], 1);
	}
}
