/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:07:38 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/21 15:34:42 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/tokenizer.h"

int			minishell_parser(char *read_line, t_data *data);
static int	minishell_parser_check_if_empty_rl(char *read_line);

/*----------------------------------------------------------------------------*/

// int	test_minishell_parser(char *read_line, t_data *data)
// {
// 	int		i;
// 	int		j;
// 	t_list	*tmp;
// 	t_token	*token_tmp;

// 	data->parser.rl_parts_lst = NULL;
// 	data->parser.token_lst = NULL;
// 	read_line_split(read_line, &data->parser.rl_parts_lst,
// 		&data->parser.token_amount);
// 	printf("tokens amount: %d\n", data->parser.token_amount);
// 	i = 0;
// 	tmp = data->parser.rl_parts_lst;
// 	while (tmp != NULL)
// 	{
// 		printf("rl_part[%d]: %s\n", i, (char *)tmp->content);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	printf("\n");
// 	i = 0;
// 	if (tokens_creator(&data->parser, data) == 0)
// 	{
// 		token_tmp = data->parser.token_lst;
// 		while (i < data->parser.token_amount)
// 		{
// 			printf("token[%d]: %s\n", i, token_tmp->string);
// 			token_tmp = token_tmp->next;
// 			i++;
// 		}
// 		printf("\n");
// 		printf("result of tokenizer: %d\n", tokenizer(data->parser.token_lst));
// 		token_tmp = data->parser.token_lst;
// 		i = 0;
// 		while (i < data->parser.token_amount)
// 		{
// 			printf("token[%d]: %s; token_type: %d\n", i, token_tmp->string, token_tmp->type);
// 			if (token_tmp->type == T_REDIR)
// 				printf("filename of redir: %s\n", token_tmp->args[0]);
// 			else if (token_tmp->type == T_COMMAND)
// 			{
// 				j = -1;
// 				printf("command args: ");
// 				while (token_tmp->args[++j] != NULL)
// 					printf("%s ", token_tmp->args[j]);
// 				printf("\n");
// 			}
// 			token_tmp = token_tmp->next;
// 			i++;
// 		}
// 		printf("\n");
// 	}
// 	return (0);
// }

int	minishell_parser(char *read_line, t_data *data)
{
	data->parser.rl_parts_lst = NULL;
	data->parser.token_lst = NULL;
	data->parser.token_amount = 0;
	if (minishell_parser_check_if_empty_rl(read_line))
		return (1);
	add_history(read_line);
	read_line_split(read_line, &data->parser.rl_parts_lst,
		&data->parser.token_amount);
	if (tokens_creator(&data->parser, data) != 0)
	{
		data->latest_exit_status = 258;
		return (258);
	}
	if (tokenizer(data->parser.token_lst) != 0)
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
	return (result);
}
