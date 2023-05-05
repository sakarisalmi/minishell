/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:00:35 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/05 16:30:59 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"

int	test_executor(t_data *data)
{
	int	fds[2];
	int	i;

	i = -1;
	while (++i < data->executor.jobs_amount)
	{
		// 1. c
	}
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
		// builtin_executor
	else
		// normal_executor
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
		// builtin_executor
	else
		// normal_executor
	return (0);
}


/*	This function handles the execution of the read_line when there is only
	a single job and the command in it is a built-in. We do this to not to
	fork, which happens otherwise in the normal execution of commands	.*/
int	executor_builtin(t_data *data)
{
}
