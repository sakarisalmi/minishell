/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_split_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:32:59 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/26 11:42:36 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

void	rl_s_handle_quotes(char *line, t_list **rl_parts_lst, t_rl_split *t);
void	rl_s_handle_s_quotes(char *line, t_list **rl_parts_lst, t_rl_split *t);
void	rl_s_handle_greater_redir(char *line, t_list **rl_parts_lst,
			t_rl_split *t);
void	rl_s_handle_lesser_redir(char *line, t_list **rl_parts_lst,
			t_rl_split *t);
void	rl_s_handle_redir_pipe(char *line, t_list **rl_parts_lst,
			t_rl_split *t);

/*----------------------------------------------------------------------------*/

void	rl_s_handle_quotes(char *line, t_list **rl_parts_lst, t_rl_split *t)
{
	t->in_quotes = !t->in_quotes;
	if (t->in_quotes)
	{
		if (t->in_token)
			ft_strncat(ft_lstlast(*rl_parts_lst)->content,
				&line[t->i], 1);
		else
		{
			if (rl_s_add_to_list(line, rl_parts_lst, t) != 0)
				return ;
			t->in_token = 1;
			ft_strncat(ft_lstlast(*rl_parts_lst)->content, &line[t->i], 1);
		}
	}
	else
	{
		ft_strncat(ft_lstlast(*rl_parts_lst)->content, &line[t->i], 1);
		if (ft_isspace(line[t->i + 1]))
		{
			t->in_token = 0;
			t->j++;
		}
	}
}

void	rl_s_handle_s_quotes(char *line, t_list **rl_parts_lst, t_rl_split *t)
{
	t->in_single_quotes = !t->in_single_quotes;
	if (t->in_single_quotes)
	{
		if (t->in_token)
			ft_strncat(ft_lstlast(*rl_parts_lst)->content,
				&line[t->i], 1);
		else
		{
			if (rl_s_add_to_list(line, rl_parts_lst, t) != 0)
				return ;
			t->in_token = 1;
			ft_strncat(ft_lstlast(*rl_parts_lst)->content, &line[t->i], 1);
		}
	}
	else
	{
		ft_strncat(ft_lstlast(*rl_parts_lst)->content, &line[t->i], 1);
		if (ft_isspace(line[t->i + 1]))
		{
			t->in_token = 0;
			t->j++;
		}
	}
}

void	rl_s_handle_greater_redir(char *line, t_list **rl_parts_lst,
	t_rl_split *t)
{
	if (t->in_token)
	{
		t->in_token = 0;
		t->j++;
	}
	if (line[t->i + 1] == '>')
	{
		if (rl_s_add_redir_or_pipe_to_list(rl_parts_lst, 3, t) != 0)
			return ;
		ft_strcpy(ft_lstlast(*rl_parts_lst)->content, ">>");
		t->j++;
		t->i++;
	}
	else
	{
		if (rl_s_add_redir_or_pipe_to_list(rl_parts_lst, 2, t) != 0)
			return ;
		ft_strcpy(ft_lstlast(*rl_parts_lst)->content, ">");
		t->j++;
	}
}

void	rl_s_handle_lesser_redir(char *line, t_list **rl_parts_lst,
			t_rl_split *t)
{
	if (t->in_token)
	{
		t->in_token = 0;
		t->j++;
	}
	if (line[t->i + 1] == '<')
	{
		if (rl_s_add_redir_or_pipe_to_list(rl_parts_lst, 3, t) != 0)
			return ;
		ft_strcpy(ft_lstlast(*rl_parts_lst)->content, "<<");
		t->j++;
		t->i++;
	}
	else
	{
		if (rl_s_add_redir_or_pipe_to_list(rl_parts_lst, 2, t) != 0)
			return ;
		ft_strcpy(ft_lstlast(*rl_parts_lst)->content, "<");
		t->j++;
	}
}

void	rl_s_handle_redir_pipe(char *line, t_list **rl_parts_lst, t_rl_split *t)
{
	if (line[t->i] == '>' && !t->in_quotes && !t->in_single_quotes)
		rl_s_handle_greater_redir(line, rl_parts_lst, t);
	else if (line[t->i] == '<' && !t->in_quotes && !t->in_single_quotes)
		rl_s_handle_lesser_redir(line, rl_parts_lst, t);
	else if (line[t->i] == '|' && !t->in_quotes && !t->in_single_quotes)
	{
		if (t->in_token)
		{
			t->in_token = 0;
			t->j++;
		}
		if (rl_s_add_redir_or_pipe_to_list(rl_parts_lst, 2, t) != 0)
			return ;
		ft_strcpy(ft_lstlast(*rl_parts_lst)->content, "|");
		t->j++;
	}
}
