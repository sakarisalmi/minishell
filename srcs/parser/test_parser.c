/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:08:27 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/26 15:17:18 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

void	print_rl_parts(t_data *data);
void	print_tunp(t_data *data);

/*----------------------------------------------------------------------------*/

void	print_rl_parts(t_data *data)
{
	int		i;
	t_list	*tmp;

	printf("\n---rl_parts results---\n");
	i = 0;
	tmp = data->parser.rl_parts_lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	printf("rl_parts amount: %d\n", i);
	i = 0;
	tmp = data->parser.rl_parts_lst;
	while (tmp)
	{
		printf("rl_parts[%d]: %s\n", i, tmp->content);
		i++;
		tmp = tmp->next;
	}
	printf("---end of rl_parts results---\n\n");
}

void	print_tunp(t_data *data)
{
	int		i;
	t_token	*tmp;

	printf("\n---tunp results---\n");
	printf("tokens amount: %d\n", data->parser.token_amount);
	tmp = data->parser.token_lst;
	i = 0;
	while (tmp)
	{
		printf("tokens_lst[%d]: %s\n", i, tmp->string);
		i++;
		tmp = tmp->next;
	}
	printf("---end of tunp results---\n\n");
}
