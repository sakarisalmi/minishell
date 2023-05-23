/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:26:18 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/23 17:38:33 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"
#include "../../include/executor.h"

int			process_handle_redirs(t_process *proc, t_data *data,
				t_executor_function *f);
static int	process_handle_redirs_lessers(t_process *proc, int idx,
				t_data *data, t_executor_function *f);
static int	process_handle_redirs_greaters(t_process *proc, int idx,
				t_executor_function *f);

/*----------------------------------------------------------------------------*/

/*	This function handles a proc's redirections. It will iterate through all
	of the tokens, and handle all of the redirections, constantly updating
	the stdin and stdout with the latest redirs. If the redir fails
	(let's say the infile doesn't exist), this function will return a value
	under zero, after which stop the proc and set exit status */
int	process_handle_redirs(t_process *proc, t_data *data, t_executor_function *f)
{
	int	latest_result;
	int	i;

	latest_result = 0;
	i = -1;
	while (proc->tokens_array[++i])
	{
		if (proc->tokens_array[i]->type == T_REDIR)
		{
			if (proc->tokens_array[i]->string[0] == '<')
				latest_result = process_handle_redirs_lessers(proc, i, data, f);
			else
				latest_result = process_handle_redirs_greaters(proc, i, f);
		}
		if (latest_result < 0)
			return (latest_result);
	}
	return (0);
}

static int	process_handle_redirs_lessers(t_process *proc, int idx,
	t_data *data, t_executor_function *f)
{
	int	result;

	if (ft_strncmp(proc->tokens_array[idx]->string, "<", 2) == 0)
		result = handle_redir_lesser(proc->tokens_array[idx], f);
	else
	{
		if (executor_set_up_here_doc_pipe(&data->executor, get_process_idx(proc,
					data)) != 0)
			return (-1);
		result = handle_redir_lesser_lesser(proc->tokens_array[idx],
				proc, data);
	}
	if (result < 0)
		return (result);
	if (proc->fd_in != STDIN_FILENO && proc->fd_in != result)
		close(proc->fd_in);
	proc->fd_in = result;
	return (0);
}

static int	process_handle_redirs_greaters(t_process *proc, int idx,
	t_executor_function *f)
{
	int	result;

	if (ft_strncmp(proc->tokens_array[idx]->string, ">", 2) == 0)
		result = handle_redir_greater(proc->tokens_array[idx], f);
	else
		result = handle_redir_greater_greater(proc->tokens_array[idx], f);
	if (result < 0)
		return (result);
	if (proc->fd_out != STDOUT_FILENO && proc->fd_out != result)
		close(proc->fd_out);
	proc->fd_out = result;
	return (0);
}
