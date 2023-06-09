/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:28:19 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/12 15:00:34 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/builtin.h"

t_token	*token_lst_init_new_node(char *token_string, t_data *data);
void	token_lst_addback(t_token **token_lst, t_token *new_node);
t_token	*token_lst_last(t_token *token_lst);
void	token_lst_del_node(t_token *token_node);
void	token_lst_clear_lst(t_token **token_lst);

/*----------------------------------------------------------------------------*/

t_token	*token_lst_init_new_node(char *token_string, t_data *data)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node || !token_string)
	{
		ft_putendl_fd("tokens_creator; malloc failure; FATAL ERROR", 2);
		if (new_node)
			free(new_node);
		if (token_string)
			free(token_string);
		read_line_parts_clean_up(data);
		minishell_loop_clean_up(data);
		exit (-1);
	}
	new_node->type = 0;
	new_node->string = token_string;
	new_node->rl_part_string = NULL;
	new_node->args = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	token_lst_addback(t_token **token_lst, t_token *new_node)
{
	t_token	*tmp;

	tmp = *token_lst;
	if (!new_node)
	{
		ft_putendl_fd("token_lst_addback, no new_node", 2);
		return ;
	}
	if (!*token_lst)
		*token_lst = new_node;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

t_token	*token_lst_last(t_token *token_lst)
{
	t_token	*tmp;

	if (!token_lst)
		return (token_lst);
	tmp = token_lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	token_lst_del_node(t_token *token_node)
{
	if (token_node)
	{
		free(token_node->string);
		free(token_node);
	}
}

void	token_lst_clear_lst(t_token **token_lst)
{
	t_token	*tmp;

	if (!token_lst)
		return ;
	while (*token_lst)
	{
		tmp = (*token_lst)->next;
		token_lst_del_node(*token_lst);
		*token_lst = tmp;
	}
}
