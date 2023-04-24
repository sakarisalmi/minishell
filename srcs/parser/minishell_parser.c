/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:07:38 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/24 15:12:34 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenize.h"

int	minishell_parser(char *read_line, t_data *data)
{
	int		i;
	t_list	*tmp;
	t_token	*token_tmp;

	data->parser.rl_parts_ls = NULL;
	data->parser.token_ls = NULL;
	read_line_split(read_line, &data->parser.rl_parts_ls,
		&data->parser.token_amount);
	printf("tokens amount: %d\n", data->parser.token_amount);
	i = 0;
	tmp = data->parser.rl_parts_ls;
	while (tmp != NULL)
	{
		printf("rl_part[%d]: %s\n", i, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	printf("\n");
	i = 0;
	if (tokens_creator(&data->parser, data) == 0)
	{
		token_tmp = data->parser.token_ls;
		while (i < data->parser.token_amount)
		{
			printf("token[%d]: %s\n", i, token_tmp->string);
			token_tmp = token_tmp->next;
			i++;
		}
	ft_lstclear(&data->parser.rl_parts_ls, free);
	token_lst_clear_ls(&data->parser.token_ls);
	printf("\n");
	}
	return (0);
}
