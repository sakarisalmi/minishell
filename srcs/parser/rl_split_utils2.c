/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_split_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:34:15 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/26 17:03:28 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

void	rl_s_handle_whitespace(char *line, t_list **rl_parts_lst,
			t_rl_split *t);
int		rl_s_add_to_list(char *line, t_list **rl_parts_ls, t_rl_split *t);
int		rl_s_add_redir_or_pipe_to_list(t_list **rl_parts_ls, int size,
			t_rl_split *t);

/*----------------------------------------------------------------------------*/

void	rl_s_handle_whitespace(char *line, t_list **rl_parts_lst, t_rl_split *t)
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
			if (rl_s_add_to_list(line, rl_parts_lst, t) != 0)
				return ;
			t->in_token = 1;
		}
		ft_strncat(ft_lstlast(*rl_parts_lst)->content, &line[t->i], 1);
	}
}

/*	This function was created to protect for possible malloc failures. Returns
	zero if everything goes as it should. */
int	rl_s_add_to_list(char *line, t_list **rl_parts_ls, t_rl_split *t)
{
	char	*new_str;
	t_list	*new_node;

	new_str = ft_calloc(ft_strlen(&line[t->i]) + 1, sizeof(char));
	if (!new_str)
	{
		ft_putendl_fd("MINISHELL: read_line_split malloc failure", 2);
		t->failure = 1;
		return (1);
	}
	new_node = ft_lstnew(new_str);
	if (!new_node)
	{
		ft_putendl_fd("MINISHELL: read_line_split malloc failure", 2);
		free(new_str);
		t->failure = 1;
		return (2);
	}
	ft_lstadd_back(rl_parts_ls, new_node);
	return (0);
}

/*	This function was created to protect for possible malloc failures. Returns
	zero if everything goes as it should. */
int	rl_s_add_redir_or_pipe_to_list(t_list **rl_parts_ls, int size,
	t_rl_split *t)
{
	char	*new_str;
	t_list	*new_node;

	new_str = ft_calloc(size, sizeof(char));
	if (!new_str)
	{
		ft_putendl_fd("MINISHELL: read_line_split malloc failure", 2);
		t->failure = 1;
		return (1);
	}
	new_node = ft_lstnew(new_str);
	if (!new_node)
	{
		ft_putendl_fd("MINISHELL: read_line_split malloc failure", 2);
		free(new_str);
		t->failure = 1;
		return (2);
	}
	ft_lstadd_back(rl_parts_ls, new_node);
	return (0);
}
