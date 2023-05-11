/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PARSER.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:17:38 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/25 14:21:24 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

enum e_token_unpacker_error_code
{
	T_NO_ERROR,
	T_UNPAIRED_QUOTE,
	T_UNPAIRED_S_QUOTE,
	T_FORBIDDEN_SYMBOL,
	T_PARSE_ERROR
};

typedef struct s_token_unpacker
{
	int	i;
	int	j;
	int	k;
	int	in_quotes;
	int	in_single_quotes;
	int	error_code;
	int	error_idx;
}	t_token_unpacker;

typedef struct s_rl_split
{
	int	i;
	int	j;
	int	k;
	int	in_quotes;
	int	in_single_quotes;
	int	in_token;
}	t_rl_split;

/*----------------------------------------------------------------------------*/

// read_line_split.c
void	read_line_split(char *line, t_list **rl_parts_ls, int *rl_parts_num);

// rl_split_utils1.c
void	rl_s_handle_quotes(char *line, t_list **rl_parts_ls, t_rl_split *t);
void	rl_s_handle_s_quotes(char *line, t_list **rl_parts_ls, t_rl_split *t);
void	rl_s_handle_greater_redir(char *line, t_list **rl_parts_ls,
			t_rl_split *t);
void	rl_s_handle_lesser_redir(char *line, t_list **rl_parts_ls,
			t_rl_split *t);
void	rl_s_handle_redir_pipe(char *line, t_list **rl_parts_ls, t_rl_split *t);

// rl_split_utils2.c
void	rl_s_handle_whitespace(char *line, t_list **rl_parts_ls, t_rl_split *t);

// token_lst_utils1.c
t_token	*token_lst_init_new_node(char *token_string);
void	token_lst_addback(t_token **token_lst, t_token *new_node);
t_token	*token_lst_last(t_token *token_lst);
void	token_lst_del_node(t_token *token_node);
void	token_lst_clear_lst(t_token **token_lst);

// tokens.creator.c
int		tokens_creator(t_parser *parser, t_data *data);

// parser_error_msg.c
int		tunp_error_msg(int error_code, char error_char);

// token_unpacker.c
int		token_unpacker(char *rl_part, t_token *token,
			t_token_unpacker *tunp, t_data *data);

// token_unpacker_get_var.c
char	*token_unpacker_hit_var(char *rl_part, char *token,
			t_token_unpacker *tunp, t_data *data);
char	*token_unpacker_get_var(char *rl_part, char *token,
			t_token_unpacker *tunp, t_data *data);
char	*token_unpacker_skip_var(char *rl_part, t_token_unpacker *tunp);

// token_unpacker_pipe_and_redir.c
void	token_unpacker_pipe_and_redir(t_token *token, char *rl_part);

// parser_clean_up.c
void	tokens_clean_up(t_data *data);
void	read_line_clean_up(t_data *data);

#endif