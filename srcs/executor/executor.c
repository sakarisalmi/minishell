/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:00:35 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/09 11:04:31 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"

int	test_executor(t_data *data);
int	test_executor_pre_setup(t_data *data);
int	test_executor_builtin(t_job *job, t_data *data);
int	executor_exec_cmd(t_job *job, t_data *data);

/*----------------------------------------------------------------------------*/

/*	this function is used when there are pipes in the read line. */
int	test_executor(t_data *data)
{
	int	result;
	int	pid;
	int	i;

	printf("in test_executor\n");
	i = -1;
	while (++i < data->executor.jobs_amount)
	{
		printf("test_executor (job[%d])\n", i);
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
			close_pipe_ends_parent_process(data->executor.fds_array[i]);
		}
	}
	// continue
	/*	possible issue; what if the final job reads from a file that doesn't exist,
		but then you do the waitpid and set a different exit code as the with that?*/
	if (result == 0)
		waitpid(pid, &data->latest_exit_status, 0);
	else
		data->latest_exit_status = result;
	return (0);
}

int	test_executor_pre_setup(t_data *data)
{
	int	i;
	int	j;

	data->executor.token_lst = data->parser.token_lst;
	data->executor.jobs_array = create_jobs_from_tokens(
			data->executor.token_lst);
	i = 0;
	while (data->executor.jobs_array[i])
		i++;
	data->executor.jobs_amount = i;
	
	// printing results
	printf("amount of jobs: %d\n", data->executor.jobs_amount);
	i = 0;
	while (i < data->executor.jobs_amount)
	{
		printf("jobs_array[%d]: ", i);
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
		printf("creating fds array for piping\n");
		data->executor.fds_array = fds_array_create_fds_for_piping(data->executor.jobs_amount);
		printf("setting up piping between jobs\n");
		if (executor_pipe_set_up(&data->executor) != 0)
		{
			printf("executor_pipe_set_up failed\n");
			return (1);
		}
		test_executor(data);
	}
	return (0);
}

// int	real_executor_pre_setup(t_data *data)
// {
// 	int	i;

// 	data->executor.token_lst = data->parser.token_lst;
// 	data->executor.jobs_array = create_jobs_from_tokens(
// 			data->executor.token_lst);
// 	i = 0;
// 	while (data->executor.jobs_array[i])
// 		i++;
// 	data->executor.jobs_amount = i;
// 	if (data->executor.jobs_amount == 1
// 		&& check_for_builtin(data->executor.jobs_array[0]->tokens_array))
// 		// builtin_executor
// 	else
// 		// normal_executor
// 	return (0);
// }


/*	This function handles the execution of the read_line when there is only
	a single job and the command in it is a built-in. We do this to not to
	fork, which happens otherwise in the normal execution of commands	.*/
int	test_executor_builtin(t_job *job, t_data *data)
{
	if (*job->fd_in != STDIN_FILENO)
		dup2(*job->fd_in, STDIN_FILENO);
	if (*job->fd_out != STDOUT_FILENO)
		dup2(*job->fd_out, STDOUT_FILENO);
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
int	executor_exec_cmd(t_job *job, t_data *data)
{
	t_token	*cmd_token;

	if (*job->fd_in != STDIN_FILENO)
		dup2(*job->fd_in, STDIN_FILENO);
	if (*job->fd_out != STDOUT_FILENO)
		dup2(*job->fd_out, STDOUT_FILENO);
	// cmd_token built-in func here?
	cmd_token = job_get_cmd_token(job);
	if (cmd_token)
	{
		job->cmd_path = find_cmd_path(cmd_token->string, data->envs);
		if (!job->cmd_path)
		{
			ft_putstr_fd("MINISHELL: ", 2);
			ft_putstr_fd(cmd_token->string, 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
		if (execve(job->cmd_path, cmd_token->args, data->envs) < 0)
		{
			perror("MINISHELL: execve");
			exit(1);
		}
	}
	exit(0);
}
