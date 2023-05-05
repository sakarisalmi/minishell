/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:00:35 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/04 13:20:43 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"

int	test_executor(t_data *data)
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
	return (0);
}

int	real_executor(t_data *data)
{
	int	i;

	data->executor.token_lst = data->parser.token_lst;
	data->executor.jobs_array = create_jobs_from_tokens(
			data->executor.token_lst);
	i = 0;
	while (data->executor.jobs_array[i])
		i++;
	data->executor.jobs_amount = i;
	return (0);
}

/*	This function handles the execution of single jobs.
	(do the redirictions first?) We check if
	there is a command in the job. Then we check if the
	command is a built-in, if not we fork the process and
	execute the command. */
int	executor_handle_single_job(t_job *job, t_data *data)
{
	// 1. handle redirs?
	data->latest_exit_status = job_handle_redirs(job, data);
	// 2. check for built-in

	// 		a. if no built-in, fork
	// 		b. if built-in, check wether to fork or not
	// 			(depends on the command)
	// 4. execute command
	// 5. save exit_status if child
	return (0);
}
