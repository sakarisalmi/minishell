/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_split_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:32:59 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/24 13:23:43 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenize.h"

void	rl_s_handle_quotes(char *line, t_list **rl_parts_ls, t_rl_split *t);
void	rl_s_handle_s_quotes(char *line, t_list **rl_parts_ls, t_rl_split *t);
void	rl_s_handle_greater_redir(char *line, t_list **rl_parts_ls,
			t_rl_split *t);
void	rl_s_handle_lesser_redir(char *line, t_list **rl_parts_ls,
			t_rl_split *t);
void	rl_s_handle_redir_pipe(char *line, t_list **rl_parts_ls, t_rl_split *t);

/*----------------------------------------------------------------------------*/

void	rl_s_handle_quotes(char *line, t_list **rl_parts_ls, t_rl_split *t)
{
	t->in_quotes = !t->in_quotes;
	if (t->in_quotes)
	{
		if (t->in_token)
			ft_strncat(ft_lstlast(*rl_parts_ls)->content,
				&line[t->i], 1);
		else
		{
			ft_lstadd_back(rl_parts_ls,
				ft_lstnew(malloc(ft_strlen((line + t->i)) * sizeof(char))));
			t->in_token = 1;
			ft_strncat(ft_lstlast(*rl_parts_ls)->content, &line[t->i], 1);
		}
	}
	else
	{
		ft_strncat(ft_lstlast(*rl_parts_ls)->content, &line[t->i], 1);
		if (ft_isspace(line[t->i + 1]))
		{
			t->in_token = 0;
			t->j++;
		}
	}
}

void	rl_s_handle_s_quotes(char *line, t_list **rl_parts_ls, t_rl_split *t)
{
	t->in_single_quotes = !t->in_single_quotes;
	if (t->in_single_quotes)
	{
		if (t->in_token)
			ft_strncat(ft_lstlast(*rl_parts_ls)->content,
				&line[t->i], 1);
		else
		{
			ft_lstadd_back(rl_parts_ls,
				ft_lstnew(malloc(ft_strlen((line + t->i)) * sizeof(char))));
			t->in_token = 1;
			ft_strncat(ft_lstlast(*rl_parts_ls)->content, &line[t->i], 1);
		}
	}
	else
	{
		ft_strncat(ft_lstlast(*rl_parts_ls)->content, &line[t->i], 1);
		if (ft_isspace(line[t->i + 1]))
		{
			t->in_token = 0;
			t->j++;
		}
	}
}

void	rl_s_handle_greater_redir(char *line, t_list **rl_parts_ls,
	t_rl_split *t)
{
	if (t->in_token)
	{
		t->in_token = 0;
		t->j++;
	}
	if (line[t->i + 1] == '>')
	{
		ft_lstadd_back(rl_parts_ls, ft_lstnew(malloc(3 * sizeof(char))));
		ft_strcpy(ft_lstlast(*rl_parts_ls)->content, ">>");
		t->j++;
		t->i++;
	}
	else
	{
		ft_lstadd_back(rl_parts_ls, ft_lstnew(malloc(2 * sizeof(char))));
		ft_strcpy(ft_lstlast(*rl_parts_ls)->content, ">");
		t->j++;
	}
}

void	rl_s_handle_lesser_redir(char *line, t_list **rl_parts_ls,
			t_rl_split *t)
{
	if (t->in_token)
	{
		t->in_token = 0;
		t->j++;
	}
	if (line[t->i + 1] == '<')
	{
		ft_lstadd_back(rl_parts_ls, ft_lstnew(malloc(3 * sizeof(char))));
		ft_strcpy(ft_lstlast(*rl_parts_ls)->content, "<<");
		t->j++;
		t->i++;
	}
	else
	{
		ft_lstadd_back(rl_parts_ls, ft_lstnew(malloc(2 * sizeof(char))));
		ft_strcpy(ft_lstlast(*rl_parts_ls)->content, "<");
		t->j++;
	}
}

void	rl_s_handle_redir_pipe(char *line, t_list **rl_parts_ls, t_rl_split *t)
{
	if (line[t->i] == '>' && !t->in_quotes && !t->in_single_quotes)
		rl_s_handle_greater_redir(line, rl_parts_ls, t);
	else if (line[t->i] == '<' && !t->in_quotes && !t->in_single_quotes)
		rl_s_handle_lesser_redir(line, rl_parts_ls, t);
	else if (line[t->i] == '|' && !t->in_quotes && !t->in_single_quotes)
	{
		if (t->in_token)
		{
			t->in_token = 0;
			t->j++;
		}
		ft_lstadd_back(rl_parts_ls, ft_lstnew(malloc(2 * sizeof(char))));
		ft_strcpy(ft_lstlast(*rl_parts_ls)->content, "|");
		t->j++;
	}
}


// void	rl_s_handle_quotes(char *line, char *rl_parts[], t_rl_split *t)
// {
// 	t->in_quotes = !t->in_quotes;
// 	if (t->in_quotes)
// 	{
// 		if (t->in_token)
// 			ft_strncat(rl_parts[t->j], &line[t->i], 1);
// 		else
// 		{
// 			rl_parts[t->j] = malloc(ft_strlen(line) * sizeof(char));
// 			ft_memset(rl_parts[t->j], 0, ft_strlen(line));
// 			t->in_token = 1;
// 			ft_strncat(rl_parts[t->j], &line[t->i], 1);
// 		}
// 	}
// 	else
// 	{
// 		ft_strncat(rl_parts[t->j], &line[t->i], 1);
// 		if (ft_isspace(line[t->i + 1]))
// 		{
// 			t->in_token = 0;
// 			t->j++;
// 		}
// 	}
// }

// void	rl_s_handle_s_quotes(char *line, char *rl_parts[], t_rl_split *t)
// {
// 	t->in_single_quotes = !t->in_single_quotes;
// 	if (t->in_single_quotes)
// 	{
// 		if (t->in_token)
// 			ft_strncat(rl_parts[t->j], &line[t->i], 1);
// 		else
// 		{
// 			rl_parts[t->j] = malloc(ft_strlen(line) * sizeof(char));
// 			ft_memset(rl_parts[t->j], 0, ft_strlen(line));
// 			t->in_token = 1;
// 			ft_strncat(rl_parts[t->j], &line[t->i], 1);
// 		}
// 	}
// 	else
// 	{
// 		ft_strncat(rl_parts[t->j], &line[t->i], 1);
// 		if (ft_isspace(line[t->i + 1]))
// 		{
// 			t->in_token = 0;
// 			t->j++;
// 		}
// 	}
// }

// void	rl_s_handle_greater_redir(char *line, char *rl_parts[], t_rl_split *t)
// {
// 	if (t->in_token)
// 	{
// 		t->in_token = 0;
// 		t->j++;
// 	}
// 	if (line[t->i + 1] == '>')
// 	{
// 		rl_parts[t->j] = malloc(3 * sizeof(char));
// 		ft_strcpy(rl_parts[t->j], ">>");
// 		t->j++;
// 		t->i++;
// 	}
// 	else
// 	{
// 		rl_parts[t->j] = malloc(2 * sizeof(char));
// 		ft_strcpy(rl_parts[t->j], ">");
// 		t->j++;
// 	}
// }

// void	rl_s_handle_lesser_redir(char *line, char *rl_parts[], t_rl_split *t)
// {
// 	if (t->in_token)
// 	{
// 		t->in_token = 0;
// 		t->j++;
// 	}
// 	if (line[t->i + 1] == '<')
// 	{
// 		rl_parts[t->j] = malloc(3 * sizeof(char));
// 		ft_strcpy(rl_parts[t->j], "<<");
// 		t->j++;
// 		t->i++;
// 	}
// 	else
// 	{
// 		rl_parts[t->j] = malloc(2 * sizeof(char));
// 		ft_strcpy(rl_parts[t->j], "<");
// 		t->j++;
// 	}
// }

// void	rl_s_handle_redir_pipe(char *line, char *rl_parts[], t_rl_split *t)
// {
// 	if (line[t->i] == '>' && !t->in_quotes && !t->in_single_quotes)
// 		rl_s_handle_greater_redir(line, rl_parts, t);
// 	else if (line[t->i] == '<' && !t->in_quotes && !t->in_single_quotes)
// 		rl_s_handle_lesser_redir(line, rl_parts, t);
// 	else if (line[t->i] == '|' && !t->in_quotes && !t->in_single_quotes)
// 	{
// 		if (t->in_token)
// 		{
// 			t->in_token = 0;
// 			t->j++;
// 		}
// 		rl_parts[t->j] = malloc(2 * sizeof(char));
// 		ft_strcpy(rl_parts[t->j], "|");
// 		t->j++;
// 	}
// }
