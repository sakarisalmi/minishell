/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:28:19 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/25 14:23:18 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

t_token	*token_lst_init_new_node(char *token_string)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->type = 0;
	new_node->string = token_string;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	token_lst_addback(t_token **token_lst, t_token *new_node)
{
	t_token	*tmp;

	tmp = *token_lst;
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

void	token_lst_clear_ls(t_token **token_lst)
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
