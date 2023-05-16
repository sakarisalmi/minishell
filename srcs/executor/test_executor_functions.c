/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_executor_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:30:17 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/15 15:31:22 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"

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
					exit(executor_exec_builtin(data->executor.jobs_array[i], data));
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
		data->latest_exit_status = executor_exec_builtin(data->executor.jobs_array[0], data);
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