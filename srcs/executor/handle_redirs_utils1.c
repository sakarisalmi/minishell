/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:28:16 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/17 13:48:16 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"
#include "../../include/executor.h"

int			handle_redir_greater(t_token *token);
int			handle_redir_greater_greater(t_token *token);
int			handle_redir_lesser(t_token *token);
int			handle_redir_lesser_lesser(t_token *token, t_job *job,
				t_data *data);

/*----------------------------------------------------------------------------*/

int	handle_redir_greater(t_token *token)
{
	int	result;

	result = open(token->args[0], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (result < 0)
	{
		ft_putstr_fd("MINISHELL: ", 2);
		ft_putstr_fd(token->args[0], 2);
		ft_putendl_fd(": failed to find or create file", 2);
	}
	return (result);
}

int	handle_redir_greater_greater(t_token *token)
{
	int	result;

	result = open(token->args[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (result < 0)
	{
		ft_putstr_fd("MINISHELL: ", 2);
		ft_putstr_fd(token->args[0], 2);
		ft_putendl_fd(": failed to find or create file", 2);
	}
	return (result);
}

int	handle_redir_lesser(t_token *token)
{
	int	result;

	result = open(token->args[0], O_RDONLY);
	if (result < 0)
	{
		ft_putstr_fd("MINISHELL: ", 2);
		ft_putstr_fd(token->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	return (result);
}

/*	Do later! how do you do the here_doc, check for examples!*/
int	handle_redir_lesser_lesser(t_token *token, t_job *job, t_data *data)
{
	int		process_idx;
	int		result;

	process_idx = get_proc_idx(job, data);
	if (process_idx == -1)
		return (-1);
	// global bool variable here?
	result = handle_redir_lesser_lesser_here_doc(token, data, process_idx);
	// the result value will tell if the user pressed ctrl-D or ctrl-C
	// and will return the value
	// if (result == SOME_CERTAIN_VALUE)
	// 		blaa
	// else
	return (data->executor.here_doc_array[process_idx][T_PIPE_READ]);
}
