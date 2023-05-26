/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:07:38 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/26 17:33:00 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/tokenizer.h"

int			minishell_parser(char *read_line, t_data *data);
static int	minishell_parser_check_if_empty_rl(char *read_line);
static void	minishell_parser_set_vals(t_parser *parser);

/*----------------------------------------------------------------------------*/

int	minishell_parser(char *read_line, t_data *data)
{
	minishell_parser_set_vals(&data->parser);
	if (minishell_parser_check_if_empty_rl(read_line))
		return (1);
	add_history(read_line);
	if (read_line_split(read_line, &data->parser.rl_parts_lst,
			&data->parser.token_amount) != 0)
	{
		free(read_line);
		data->latest_exit_status = -42;
		return (-42);
	}
	free(read_line);
	print_rl_parts(data);
	if (tokens_creator(&data->parser, data) != 0)
	{
		data->latest_exit_status = 258;
		return (258);
	}
	print_tunp(data);
	if (tokenizer(data->parser.token_lst, data) != 0)
	{
		data->latest_exit_status = 258;
		return (258);
	}
	return (0);
}

/*	This function checks if the read line was empty, if so, do not proceed. 
	returns 1 if the string is empty, else return 0. */
static int	minishell_parser_check_if_empty_rl(char *read_line)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (read_line[i])
	{
		if (!ft_isspace(read_line[i]))
			result = 0;
		i++;
	}
	if (result == 1)
		free (read_line);
	return (result);
}

static void	minishell_parser_set_vals(t_parser *parser)
{
	parser->rl_parts_lst = NULL;
	parser->token_lst = NULL;
	parser->token_amount = 0;
}
