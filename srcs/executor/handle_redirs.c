/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:26:18 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/17 13:31:49 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"
#include "../../include/executor.h"

int			job_handle_redirs(t_job *job, t_data *data);
static int	job_handle_redirs_lessers(t_job *job, int idx, t_data *data);
static int	job_handle_redirs_greaters(t_job *job, int idx);

/*----------------------------------------------------------------------------*/

/*	This function handles a job's redirections. It will iterate through all
	of the tokens, and handle all of the redirections, constantly updating
	the stdin and stdout with the latest redirs. If the redir fails
	(let's say the infile doesn't exist), this function will return a value
	under zero, after which stop the job and set exit status */
int	job_handle_redirs(t_job *job, t_data *data)
{
	int	latest_result;
	int	i;

	latest_result = 0;
	i = -1;
	while (job->tokens_array[++i])
	{
		if (job->tokens_array[i]->type == T_REDIR)
		{
			if (job->tokens_array[i]->string[0] == '<')
				latest_result = job_handle_redirs_lessers(job, i, data);
			else
				latest_result = job_handle_redirs_greaters(job, i);
		}
		if (latest_result < 0)
			return (latest_result);
	}
	return (0);
}

static int	job_handle_redirs_lessers(t_job *job, int idx, t_data *data)
{
	int	result;
	int	old_here_doc_bool;

	old_here_doc_bool = job->here_doc_bool;
	if (ft_strncmp(job->tokens_array[idx]->string, "<", 2) == 0)
	{
		result = handle_redir_lesser(job->tokens_array[idx]);
		job->here_doc_bool = 0;
	}
	else
	{
		if (executor_set_up_here_doc_pipe(&data->executor, get_proc_idx(job,
					data)) != 0)
			return (-1);
		result = handle_redir_lesser_lesser(job->tokens_array[idx], job, data);
		job->here_doc_bool = 1;
	}
	if (result < 0)
		return (result);
	if (job->fd_in != STDIN_FILENO && job->fd_in != result
		&& !old_here_doc_bool)
		close(job->fd_in);
	job->fd_in = result;
	return (0);
}

static int	job_handle_redirs_greaters(t_job *job, int idx)
{
	int	result;

	if (ft_strncmp(job->tokens_array[idx]->string, ">", 2) == 0)
		result = handle_redir_greater(job->tokens_array[idx]);
	else
		result = handle_redir_greater_greater(job->tokens_array[idx]);
	if (result < 0)
		return (result);
	if (job->fd_out != STDOUT_FILENO && job->fd_out != result)
		close(job->fd_out);
	job->fd_out = result;
	return (0);
}
