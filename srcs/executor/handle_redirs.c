/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:26:18 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/09 11:05:14 by ssalmi           ###   ########.fr       */
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

	if (ft_strncmp(job->tokens_array[idx]->string, "<", 2) == 0)
		result = handle_redir_lesser(job->tokens_array[idx]);
	else
		result = handle_redir_lesser_lesser(job->tokens_array[idx], data);
	if (result < 0)
		return (result);
	job->fd_in = &result;
	return (0);
}

static int	job_handle_redirs_greaters(t_job *job, int idx)
{
	int	result;

	if (ft_strncmp(job->tokens_array[idx]->string, ">", 2) == 0)
	{
		result = handle_redir_greater(job->tokens_array[idx]);
		job->append_mode = 0;
	}
	else
	{
		result = handle_redir_greater_greater(job->tokens_array[idx]);
		job->append_mode = 1;
	}
	if (result < 0)
		return (result);
	job->fd_out = &result;
	return (0);
}
