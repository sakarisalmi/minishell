/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:00:35 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/12 12:45:36 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"

int		test_executor(t_data *data);
int		real_executor(t_executor *ex, t_data *data);
int		test_executor_pre_setup(t_data *data);
int		real_executor_pre_setup(t_data *data);
int		test_executor_builtin(t_job *job, t_data *data);
void	executor_exec_cmd(t_job *job, t_data *data);

/*----------------------------------------------------------------------------*/

/*	this function is used when there are pipes in the read line. */
int	test_executor(t_data *data)
{
	int	result;
	int	pid;
	int	i;
	int	pgid;

	printf("\tIN TEST_EXECUTOR\n");
	i = -1;
	pgid = getpgrp();
	printf("\t\tthe pgid is %d\n", pgid);
	while (++i < data->executor.jobs_amount)
	{
		printf("\ttest_executor (job[%d])\n", i);
		// do redirs (already set up pipe fd's)
		result = job_handle_redirs(
				data->executor.jobs_array[i], data);
		if (result == 0)
		{
			// if handle redirs is successful, fork and execute job
			pid = fork();
			if (pid == 0)
			{
				// check if the command in the job is a built-in and if so,
				// go to function executor_builtin, else the normal executor
				if (check_for_builtin(data->executor.jobs_array[i]->tokens_array))
					exit(test_executor_builtin(data->executor.jobs_array[i], data));
				executor_exec_cmd(data->executor.jobs_array[i], data);
			}
			else if (pid < 0)
			{
				perror("MINISHELL: fork");
				return (-1);
			}
			printf("\tTEST_EXECUTOR; stage 1\n");
			if (i != 0)
				close_pipe_ends_parent_process(data->executor.fds_array[i - 1]);
			printf("\tTEST_EXECUTOR; stage 2\n");
			waitpid(WAIT_ANY, &data->latest_exit_status, 0);
		}
	}
	printf("\tTEST_EXECUTOR; parent process, after job iteration\n");
	// continue
	/*	possible issue; what if the final job reads from a file that doesn't exist,
		but then you do the waitpid and set a different exit code as the with that?*/
	// if (result == 0)
	// while (waitpid(-pgid, &data->latest_exit_status, 0))
	// 	;
	// else
		// data->latest_exit_status = result;
	printf("\tEND OF TEST_EXECUTOR\n");
	return (0);
}

int	real_executor(t_executor *ex, t_data *data)
{
	t_executor_function	f;

	f.i = -1;
	while (++f.i < ex->jobs_amount)
	{
		f.result = job_handle_redirs(ex->jobs_array[f.i], data);
		if (f.result == 0)
		{
			f.pid = fork();
			if (f.pid == 0)
			{
				if (check_for_builtin(ex->jobs_array[f.i]->tokens_array))
					exit(test_executor_builtin(ex->jobs_array[f.i], data));
				executor_exec_cmd(ex->jobs_array[f.i], data);
			}
			else if (f.pid < 0)
				return (executor_error_msg(NULL, 1));
			if (f.i != 0)
				close_pipe_ends_parent_process(ex->fds_array[f.i - 1]);
		}
	}
	if (f.result != 0)
		return (f.result);
	waitpid(f.pid, &f.result, 0);
	return (executor_get_latest_exit_status(f.result));
}

int	test_executor_pre_setup(t_data *data)
{
	int	i;
	int	j;

	printf("IN TEST_EXECUTOR_PRE_SETUP\n");
	data->executor.token_lst = data->parser.token_lst;
	data->executor.jobs_array = create_jobs_from_tokens(
			data->executor.token_lst);
	i = 0;
	while (data->executor.jobs_array[i])
		i++;
	data->executor.jobs_amount = i;
	printf("amount of jobs: %d\n", data->executor.jobs_amount);
	i = 0;
	while (i < data->executor.jobs_amount)
	{
		printf("\tjobs_array[%d]: ", i);
		j = -1;
		while (data->executor.jobs_array[i]->tokens_array[++j])
			printf("%s, ", data->executor.jobs_array[i]->tokens_array[j]->string);
		printf("\n");
		i++;
	}
	printf("\n");
	// if there is only one job and the cmd is a built-in, go into a different function
	// else go in another that handles pipes and subshells
	if (data->executor.jobs_amount == 1 && check_for_builtin(data->executor.jobs_array[0]->tokens_array))
	{
		// builtin_executor
		printf("BUILTIN_EXECUTOR\n");
		data->latest_exit_status = test_executor_builtin(data->executor.jobs_array[0], data);
	}
	else
	{
		// normal_executor
		printf("NORMAL_EXECUTOR\n");
		if (data->executor.jobs_amount > 1)
		{
			printf("setting up piping between jobs\n");
			if (executor_pipe_set_up(&data->executor) != 0)
				executor_error_msg(NULL, 2);
		}
		printf("going into test_executor\n");
		test_executor(data);
	}
	return (0);
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
	child_process_close_all_fds(&data->executor);
	cmd_token = job_get_cmd_token(job);
	if (cmd_token)
	{
		job->cmd_path = find_cmd_path(cmd_token->string, data->envs);
		if (!job->cmd_path)
			exit(executor_error_msg(cmd_token->string, 4));
		if (execve(job->cmd_path, cmd_token->args, data->envs) < 0)
			exit(executor_error_msg(NULL, 3));
	}
	exit(0);
}
