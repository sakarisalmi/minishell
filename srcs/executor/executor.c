/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:00:35 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/18 13:04:16 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"

int		real_executor(t_executor *ex, t_data *data);
int		real_executor_pre_setup(t_data *data);
int		test_executor_builtin(t_job *job, t_data *data);
void	executor_exec_cmd(t_job *job, t_data *data);

/*----------------------------------------------------------------------------*/

int	real_executor(t_executor *ex, t_data *data)
{
	t_executor_function	f;

	executor_start(&f, ex);
	while (++f.i < ex->jobs_amount)
	{
		f.result = executor_check_if_to_fork(&f, ex, data);
		if (f.result == 0)
		{
			f.pid[f.i] = fork();
			if (f.pid[f.i] == 0)
			{
				if (check_for_builtin(ex->jobs_array[f.i]->tokens_array))
					exit(test_executor_builtin(ex->jobs_array[f.i], data));
				executor_exec_cmd(ex->jobs_array[f.i], data);
			}
			else if (f.pid[f.i] < 0)
				return (executor_error_msg(NULL, 1));
			close_pipe_ends_parent_process(ex->here_doc_array[f.i]);
			if (f.i != 0)
				close_pipe_ends_parent_process(ex->fds_array[f.i - 1]);
		}
	}
	return (executor_end(&f, ex));
}

int	real_executor_pre_setup(t_data *data)
{
	int	i;

	data->executor.token_lst = data->parser.token_lst;
	data->executor.jobs_array = create_jobs_from_tokens(
			data->executor.token_lst);
	i = 0;
	while (data->executor.jobs_array[i])
		i++;
	data->executor.jobs_amount = i;
	data->executor.here_doc_array = \
		executor_set_up_here_doc_array(&data->executor);
	if (data->executor.jobs_amount == 1
		&& check_for_builtin(data->executor.jobs_array[0]->tokens_array))
		return (test_executor_builtin(data->executor.jobs_array[0], data));
	else
	{
		if (data->executor.jobs_amount > 1)
		{
			if (executor_pipe_set_up(&data->executor) != 0)
				return (executor_error_msg(NULL, 2));
		}
		return (real_executor(&data->executor, data));
	}
	return (0);
}


/*	This function handles the execution of the read_line when there is only
	a single job and the command in it is a built-in. We do this to not to
	fork, which happens otherwise in the normal execution of commands	.*/
int	test_executor_builtin(t_job *job, t_data *data)
{
	if (job->fd_in != STDIN_FILENO)
		dup2(job->fd_in, STDIN_FILENO);
	if (job->fd_out != STDOUT_FILENO)
		dup2(job->fd_out, STDOUT_FILENO);
	close_all_pipe_fds(&data->executor);
	printf("IN TEST_EXECUTOR_BUILTIN; feature coming soon!\n");
	(void)data;
	return (0);
}

/*	this is the function the child process will go into to execute the job.
	First we check if the job's fd_in or fd_out are not the STDIN r STDOUT
	and if so, we will dup2 the fds. We will then check if there is a command
	in the job and if so, we will execve the command. If there is no command,
	we will exit the process with zero. 
	HUOM: what to do about built-ins? will prob have to go in another func
	(this functions line amount is close to the limit)*/
void	executor_exec_cmd(t_job *job, t_data *data)
{
	t_token	*cmd_token;

	if (job->fd_in != STDIN_FILENO)
		dup2(job->fd_in, STDIN_FILENO);
	if (job->fd_out != STDOUT_FILENO)
		dup2(job->fd_out, STDOUT_FILENO);
	close_all_pipe_fds(&data->executor);
	cmd_token = job_get_cmd_token(job);
	if (job->cmd_path)
	{
		if (execve(job->cmd_path, cmd_token->args, data->envs) < 0)
			exit(executor_error_msg(NULL, 3));
	}
	exit(0);
}
